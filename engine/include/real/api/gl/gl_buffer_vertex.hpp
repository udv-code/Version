// Copyright (c) 2020 udv. All rights reserved.

#ifndef REAL_GL_BUFFER_VERTEX
#define REAL_GL_BUFFER_VERTEX

#include <memory>

#include "real/core.hpp"
#include "real/renderer/buffer_vertex.hpp"

namespace real {
	class REAL_API gl_vertex_buffer : public vertex_buffer {
	public:
		gl_vertex_buffer(float *data, uint32_t size);
		~gl_vertex_buffer() override;

		[[nodiscard]] const real::reference<real::vertex_array> &
		vertex_array() const override { return vertex_array_; };
		[[nodiscard]] const buffer_layout &layout() const override { return layout_; };

		void layout(std::initializer_list<vertex_attribute> attributes) override;
		void link_to(const real::reference<real::vertex_array> &vertex_array) override;

		void bind() const override;
		void unbind() const override;
	private:
		renderer_id_t renderer_id_;
		buffer_layout layout_;
		real::reference<real::vertex_array> vertex_array_;
	};
}

#endif //REAL_GL_BUFFER_VERTEX
