#include <iostream>
#include <string>
#include <vector>

struct Document;

struct IMachine
{
  virtual void print(Document& doc) = 0;
  virtual void scan(Document& doc) = 0;
  virtual void fax(Document& doc) = 0;
};

struct MFP : IMachine
{
  virtual void print(Document& doc) override
  {
    //ok
  }
  virtual void scan(Document& doc) override
  {
    //ok
  }
  virtual void fax(Document& doc) override
  {
    //ok
  }

};

// struct Scanner : IMachine
// {
//  virtual void print(Document& doc) override
//   {
    
//   }
//   virtual void scan(Document& doc) override
//   {
//     //ok
//   }
//   virtual void fax(Document& doc) override
//   {
    
//   }
// };
  
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
  virtual void print (Document &doc) override
  {

  }
};

struct Scanner : IScanner
{
  virtual void scan(Document &doc)
  {

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

  return 0;
}
