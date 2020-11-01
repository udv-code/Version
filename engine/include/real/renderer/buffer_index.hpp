// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_INDEX_BUFFER
#define REAL_INDEX_BUFFER

#include "real/core.hpp"

namespace real {
	class REAL_API index_buffer {
	private:
	public:
		virtual ~index_buffer();

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		[[nodiscard]] virtual uint32_t count() const = 0;
	public:
		static index_buffer *make(uint32_t *data, uint32_t size);
	};
}

#endif //REAL_INDEX_BUFFER
