#pragma once

#include <string>
#include <utility>
#include <vector>

#include "Common.h"

// Helper class that manages resources for 2D-array for Luna language.
// NOTE: its sizes cannot be changed once the object is created.
class Matrix2d
{
	std::vector<std::string> cellContents; // manages memory for cell contents
	std::vector<const char *> items; // exposes strings as Luna-consumable array of C-style strings

public:
	const size_t rowCount = 0;
	const size_t columnCount = 0;

	Matrix2d(size_t rowCount, size_t columnCount);
	~Matrix2d();

	void store(size_t row, size_t column, std::string contents);

	size_t cellCount() const;
	size_t makeIndex(size_t row, size_t column) noexcept;
	const char * const *data() const noexcept;
};

extern "C"
{
	EXPORT void mat_delete(void *mat) noexcept; // NOTE: mat is not the Matrix2d object but its data() value
}
