#include <xlnt/xlnt.hpp>

#include "Matrix2d.h"
#include "Common.h"

#ifdef _MSC_VER
#ifdef _DEBUG
#pragma comment(lib, "xlntd.lib")
#else
#pragma comment(lib, "xlnt.lib")
#endif
#endif

namespace
{
	using namespace std::literals;

	auto xlsxParseFile(const char *filename)
	{
		try
		{
			xlnt::workbook wb;
			wb.load(filename);
			const auto sheet = wb.active_sheet();

			// We keep the object under unique_ptr, so there will be
			// no leak if exception is thrown before the end of function
			auto ret = std::make_unique<Matrix2d>(sheet.highest_row(), sheet.highest_column().index);

			for (auto row : sheet.rows(false))
			{
				for (auto cell : row)
				{ 
					// subtract 1, as xlsx is indexed from 1, and we are indexed from 0
					ret->store(cell.row() - 1, cell.column().index - 1, cell.to_string());
				}
			}

			return ret;
		}
		catch(std::exception &e)
		{
			throw std::runtime_error("Failed to parse file `"s + filename + "` : " + e.what());
		}
	}
}

extern "C"
{
	EXPORT Matrix2d * matrixFromXlsxFile(const char *filename) noexcept
	{
		try
		{
			// .release takes ownership of the objects and returns it to the caller
			return xlsxParseFile(filename).release(); 
		}
		catch (std::exception &)
		{
			return nullptr;
		}
	}

	EXPORT void releaseMatrix(Matrix2d *matrix) noexcept
	{
		try
		{
			delete matrix;
		}
		catch(...)
		{}
	}
}

// int main()
// {
// 	auto matrix = matrixFromXlsxFile(R"(C:\Users\mwurb\Documents\kalkulator.xlsx)");
// 	return EXIT_SUCCESS;
// }