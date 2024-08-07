#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <sstream>

enum class OutputFormat
{
	markdown, html
};

struct ListStrategy
{
	virtual void start(std::ostringstream &oss)
	{
	}

	virtual void add_list_item(std::ostringstream &oss, const std::string &item)
	{
	}

	virtual void end(std::ostringstream &oss)
	{
	}

	virtual ~ListStrategy() = default;
};

struct MarkDownStrategy : ListStrategy
{
	void start(std::ostringstream &oss) override
	{
	}

	void add_list_item(std::ostringstream &oss, const std::string &item) override
	{
		oss << "* " << item << "\n";
	}

	void end(std::ostringstream &oss) override
	{
	}
};

struct HTMLStrategy : ListStrategy
{
	void start(std::ostringstream &oss) override
	{
		oss << "<ul>\n";
	}

	void add_list_item(std::ostringstream &oss, const std::string &item) override
	{
		oss << "  <li>" << item << "</li>\n";
	}

	void end(std::ostringstream &oss) override
	{
		oss << "</ul>\n";
	}
};

class TextProcessor
{
private:
	std::ostringstream oss;
	std::unique_ptr<ListStrategy> list_strategy;
public:
	TextProcessor() = default;

	void clear()
	{
		oss.str("");
		oss.clear();
	}

	void append_list(const std::vector<std::string> &items)
	{
		list_strategy->start(oss);
		for (const std::string &item : items)
		{
			list_strategy->add_list_item(oss, item);
		}
		list_strategy->end(oss);
	}

	void set_output_format(const OutputFormat &format)
	{
		switch (format)
		{
			case OutputFormat::markdown:
				list_strategy = std::make_unique<MarkDownStrategy>();
				break;
			case OutputFormat::html:
				list_strategy = std::make_unique<HTMLStrategy>();
				break;
			default:
				break;
		}
	}

	std::string str() const
	{
		return oss.str();
	}
};

int main()
{
	const std::vector<std::string> items{"foo", "bar", "baz"};
	TextProcessor tp;
	tp.set_output_format(OutputFormat::markdown);
	tp.append_list(items);
	std::cout << tp.str() << '\n';

	tp.clear();

	tp.set_output_format(OutputFormat::html);

	tp.append_list(items);

	std::cout << tp.str() << '\n';

	return 0;
}
