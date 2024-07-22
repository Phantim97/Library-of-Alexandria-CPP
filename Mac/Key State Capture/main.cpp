//
// Created by Timothy Coelho on 7/21/24.
//
#include <ApplicationServices/ApplicationServices.h>
#include <iostream>
#include <thread>
#include <atomic>
#include "virtual_keys.h"

static std::atomic<bool> break_listener(false);

static uint64_t modifier_state = 0;

//Making the name similar to Win32
CGEventRef GetAsyncKeyState(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon)
{
	if (type == kCGEventKeyDown)
	{
		const CGKeyCode keyCode = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
		std::cout << "Key pressed: 0x" << std::hex << (keyCode) << '\n'; //Note some utility keys trigger twice

		if (keyCode == VK_ESCAPE)
		{
			break_listener = true;
			if (refcon != nullptr)
			{
				const CFRunLoopRef run_loop_ref = static_cast<CFRunLoopRef>(refcon);
				CFRunLoopStop(run_loop_ref);
				std::cout << "Breaking Loop.\n";
			}
			else
			{
				std::cerr << "refcon is null in callback.\n";
			}
		}
	}
	else if (type == kCGEventFlagsChanged)
	{
		const uint64_t modifier_state_current = CGEventGetFlags(event);

		if (modifier_state_current != modifier_state)
		{
			std::cout << "Flags changed: 0x" << std::hex << modifier_state_current << '\n';
			modifier_state = modifier_state_current;
		}
	}

	return event;
}

//Note for a listen thread I had to put all the CG/CF logic into the same function otherwise CFRunLoop() hangs
void run_listener()
{
	//kCGEventFlagsChanged for shift, control, etc.
	const CGEventMask evt_mask = CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged);

	//Event to capture key state (Current loop reference is passed to refcon)
	const CFMachPortRef key_evt_press = CGEventTapCreate(
			kCGSessionEventTap,
			kCGHeadInsertEventTap,
			kCGEventTapOptionDefault,
			evt_mask,
			GetAsyncKeyState,
			reinterpret_cast<void*>(CFRunLoopGetCurrent())
	);

	if (!key_evt_press)
	{
		std::cerr << "Failed to create event tap\n";
		return;
	}

	// Create a run loop source
	const CFRunLoopSourceRef loop_ref = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, key_evt_press, 0);

	// Add the source to the current run loop
	CFRunLoopAddSource(CFRunLoopGetCurrent(), loop_ref, kCFRunLoopCommonModes);

	// Enable the event tap
	CGEventTapEnable(key_evt_press, true);

	std::cout << "Run loop started in thread: " << std::this_thread::get_id() << '\n';
	CFRunLoopRun(); //Hangs until stop signal received from CFRunLoopStop
	std::cout << "Run loop stopped in thread: " << std::this_thread::get_id() << '\n';

	// Clean up resources
	CFRelease(loop_ref);
	CFRelease(key_evt_press);
}

int main()
{
	// Run the loop
	std::thread listener(run_listener);

	std::cout << "Listening to keyboard...\n";

	while (!break_listener)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "Teardown...\n";

	listener.join();

	return 0;
}
