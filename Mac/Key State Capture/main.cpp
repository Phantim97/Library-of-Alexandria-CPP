//
// Created by Timothy Coelho on 7/21/24.
//
#include <ApplicationServices/ApplicationServices.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <unordered_map>
#include "virtual_keys.h"

static std::atomic<bool> break_listener(false);
std::unordered_map<VirtualKey, bool> key_states;
static uint64_t modifier_state = 0;

//Making the name similar to Win32
CGEventRef GetAsyncKeyState(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon)
{
	if (type == kCGEventKeyDown)
	{
		const CGKeyCode key_code = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
		std::cout << "Key pressed: 0x" << std::hex << (key_code) << '\n'; //Note some utility keys trigger twice

		key_states[key_code] = true;

		if (key_code == VK_ESCAPE)
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
		const VirtualKey key = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
		uint64_t modifier_change = modifier_state ^ modifier_state_current;

		if (modifier_change & kCGEventFlagMaskShift)
		{
			key_states[VK_LSHIFT] = (modifier_state_current & kCGEventFlagMaskShift) && (key == VK_LSHIFT) && modifier_state_current != 0x100;
			key_states[VK_RSHIFT] = (modifier_state_current & kCGEventFlagMaskShift) && (key == VK_RSHIFT) && modifier_state_current != 0x100;
		}
		if (modifier_change & kCGEventFlagMaskControl)
		{
			key_states[VK_LCONTROL] = (modifier_state_current & kCGEventFlagMaskControl) && (key == VK_LCONTROL) && modifier_state_current != 0x100;
			key_states[VK_RCONTROL] = (modifier_state_current & kCGEventFlagMaskControl) && (key == VK_RCONTROL) && modifier_state_current != 0x100;
		}
		if (modifier_change & kCGEventFlagMaskCommand)
		{
			key_states[VK_LCOMMAND] = (modifier_state_current & kCGEventFlagMaskCommand) && (key == VK_LCOMMAND) && modifier_state_current != 0x100;
			key_states[VK_RCOMMAND] = (modifier_state_current & kCGEventFlagMaskCommand) && (key == VK_RCOMMAND) && modifier_state_current != 0x100;
		}
		if (modifier_change & kCGEventFlagMaskAlternate)
		{
			key_states[VK_LOPTION] = (modifier_state_current & kCGEventFlagMaskAlternate) && (key == VK_LOPTION) && modifier_state_current != 0x100;
			key_states[VK_ROPTION] = (modifier_state_current & kCGEventFlagMaskAlternate) && (key == VK_ROPTION) && modifier_state_current != 0x100;
		}
		if (modifier_change & kCGEventFlagMaskAlphaShift)
		{
			if (key == VK_CAPITAL) {
				// Toggle the Caps Lock state
				key_states[VK_CAPITAL] = !key_states[VK_CAPITAL];
			}
			//key_states[VK_CAPITAL] = (modifier_state_current & kCGEventFlagMaskAlphaShift) && (key == VK_CAPITAL); //The nature of caps lock means this checks while toggled
		}

		if (modifier_state_current != modifier_state)
		{
			std::cout << "Flags changed: 0x" << std::hex << modifier_state_current << '\n';
			modifier_state = modifier_state_current;
		}
	}
	else if (type == kCGEventKeyUp)
	{
		const CGKeyCode key_code = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
		key_states[key_code] = false;
	}

	return event;
}

bool key_pressed(VirtualKey key)
{
	std::unordered_map<VirtualKey, bool>::iterator it = key_states.find(key);
	if (it != key_states.end())
	{
		return it->second;
	}

	return false;
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
		if (key_pressed(VK_ESCAPE))
		{
			std::cout << "Escape key is pressed\n";
		}

		if (key_pressed(VK_LSHIFT))
		{
			std::cout << "Left Shift key is pressed.\n";
		}

		if (key_pressed(VK_RSHIFT))
		{
			std::cout << "Right Shift key is pressed.\n";
		}

		if (key_pressed(VK_LCONTROL))
		{
			std::cout << "Left Control key is pressed.\n";
		}

		if (key_pressed(VK_RCONTROL))
		{
			std::cout << "Right Control key is pressed.\n";
		}

		if (key_pressed(VK_LOPTION))
		{
			std::cout << "Left Option key is pressed.\n";
		}

		if (key_pressed(VK_ROPTION))
		{
			std::cout << "Right Option key is pressed.\n";
		}

		if (key_pressed(VK_LCOMMAND))
		{
			std::cout << "Left Command key is pressed.\n";
		}

		if (key_pressed(VK_RCOMMAND))
		{
			std::cout << "Right Command key is pressed.\n";
		}

		if (key_pressed(VK_CAPITAL))
		{
			std::cout << "Caps lock pressed\n";
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "Teardown...\n";

	listener.join();

	return 0;
}
