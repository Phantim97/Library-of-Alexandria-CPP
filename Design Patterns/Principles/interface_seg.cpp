#include <iostream>
#include <string>
#include <vector>

struct Document
{
	std::string text;
	Document(const std::string& text) : text(text) {}
};

struct IMachine
{
	virtual void print(Document& doc) = 0;
	virtual void scan(Document& doc) = 0;
	virtual void fax(Document& doc) = 0;
};

struct MFP : IMachine
{
	void print(Document& doc) override
	{
		std::cout << "Printing document: " << doc.text << '\n';
	}

	void scan(Document& doc) override
	{
		std::cout << "Scanning document: " << doc.text << '\n';
	}

	void fax(Document& doc) override
	{
		std::cout << "Faxing document: " << doc.text << '\n';
	}
};

struct IPrinter
{
	virtual void print(Document &doc) = 0;
};

struct IScanner
{
	virtual void scan(Document &doc) = 0;
};

struct Printer : IPrinter
{
	void print(Document &doc) override
	{
		std::cout << "Printing document: " << doc.text << '\n';
	}
};

struct Scanner : IScanner
{
	void scan(Document &doc) override
	{
		std::cout << "Scanning document: " << doc.text << '\n';
	}
};

struct IMachine2 : IPrinter, IScanner {};

struct Machine : IMachine2
{
	IPrinter& printer;
	IScanner& scanner;

	Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

	void print(Document &doc) override
	{
		printer.print(doc);
	}

	void scan(Document &doc) override
	{
		scanner.scan(doc);
	}
};

int main()
{
	Document doc("Hello, world!");

	Printer printer;
	Scanner scanner;

	Machine machine(printer, scanner);
	machine.print(doc);
	machine.scan(doc);

	MFP mfp;
	mfp.print(doc);
	mfp.scan(doc);
	mfp.fax(doc);

	return 0;
}
