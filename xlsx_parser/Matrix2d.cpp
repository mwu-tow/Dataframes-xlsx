#include "Matrix2d.h"

#include <unordered_map>

namespace
{
	// Note: Luna gets pointer to memory managed by Matrix2d object
	// and calls mat_delete with that pointer.
	// We need to keep this mapping, so we know what to delete.

	// TODO: at some point in future thread-safety should be considered
	// (either hide this map behind mutex or document safety requirements)
	std::unordered_map<const void*, Matrix2d*> pointersToTheirManagers;
}

Matrix2d::Matrix2d(size_t rowCount, size_t columnCount) : rowCount(rowCount), columnCount(columnCount)
{
	items.resize(cellCount());
	cellContents.resize(cellCount());

	pointersToTheirManagers[data()] = this;
}

Matrix2d::~Matrix2d()
{
	pointersToTheirManagers.erase(data());
}

size_t Matrix2d::cellCount() const
{
	return rowCount * columnCount;
}

size_t Matrix2d::makeIndex(size_t row, size_t column) noexcept
{
	return row * columnCount + column;
}

void Matrix2d::store(size_t row, size_t column, std::string contents)
{
	auto index = makeIndex(row, column);
	auto &storage = cellContents.at(index);
	storage = std::move(contents);
	items.at(index) = storage.c_str();
}

const char * const * Matrix2d::data() const noexcept
{
	return items.data();
}

extern "C" 
{
	void mat_delete(void *mat) noexcept
	{
		try
		{
			delete pointersToTheirManagers.at(mat);
		}
		catch(...) {}
	}
}
