// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_BUFFER_VERTEX
#define REAL_GL_BUFFER_VERTEX

#include <memory>

#include "real/core.hpp"
#include "real/renderer/buffer_vertex.hpp"

namespace Real
{
	class REAL_API GLVertexBuffer : public VertexBuffer
	{
	public:
		GLVertexBuffer(float* data, uint32_t size);
		~GLVertexBuffer() override;

		[[nodiscard]] const BufferLayout& Layout() const override
		{ return bufferLayout; };

		void Layout(std::initializer_list<VertexAttribute> attributes) override;

		void Bind() const override;
		void Unbind() const override;
	private:
		renderer_id_t rendererId;
		BufferLayout bufferLayout;
	};
}

#endif //REAL_GL_BUFFER_VERTEX
