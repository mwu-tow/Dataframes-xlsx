#include <xlnt/xlnt.hpp>

#pragma comment(lib, "xlntd.lib")

class TheGreatMatrix
{
	size_t rowCount = 0;
	size_t columnCount = 0;

	std::vector<std::string> cellContents; // manages memory for cell contents
	std::vector<const char *> items; // exposes strings as Luna-consumable array of C-style strings

	size_t cellCount() const { return rowCount * columnCount; }

public:
	TheGreatMatrix(const xlnt::worksheet &sheet)
		: TheGreatMatrix{sheet.highest_row(), sheet.highest_column().index}
	{
		for (auto row : sheet.rows(false)) 
		{ 
			for (auto cell : row) 
			{ 
				// subtract 1, as xlsx is indexed from 1, and we are indexed from 0
				store(cell.row() - 1, cell.column().index - 1, cell.to_string());
			}
		}
	}

	TheGreatMatrix(size_t rowCount, size_t columnCount) : rowCount(rowCount), columnCount(columnCount)
	{
		items.resize(cellCount());
		cellContents.resize(cellCount());
	}

	size_t makeIndex(size_t row, size_t column) 
	{
		return row * columnCount + column;
	}

	void store(size_t row, size_t column, std::string contents)
	{
		auto index = makeIndex(row, column);
		auto &storage = cellContents.at(index);
		storage = std::move(contents);
		items.at(index) = storage.c_str();
	}

	const char * const *data() const
	{
		return items.data();
	}
};

std::unique_ptr<TheGreatMatrix> parseMatrixFromXlsx(const char *filepath)
{
	xlnt::workbook wb;
	wb.load(R"(C:\Users\mwurb\Documents\kalkulator.xlsx)");
	xlnt::worksheet ws = wb.active_sheet();
	TheGreatMatrix mat{ws};

}

int main()
{
	xlnt::workbook wb;
	wb.load(R"(C:\Users\mwurb\Documents\kalkulator.xlsx)");
	xlnt::worksheet ws = wb.active_sheet();

	auto lastColumn = ws.highest_column().index;
	auto lastRow = ws.highest_row();

	TheGreatMatrix mat{lastRow, lastColumn};

	std::clog << "Processing spread sheet" << std::endl;
	for (auto row : ws.rows(false)) 
	{ 
		for (auto cell : row) 
		{ 
			mat.store(cell.row() - 1, cell.column().index - 1, cell.to_string());
		}
	}
	std::clog << "Processing complete" << std::endl;
	return EXIT_SUCCESS;
}

extern "C"
{
	void * matrixFromXlsxFile(const char *filename)
	{

	}

	void releaseMatrix(void *matrix)
	{
	}
}