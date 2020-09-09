// Copyright (c) 2020 udv. All rights reserved.

#include "version/application.hpp"

namespace vn {

	application::application(std::string name)
			: singleton<application>{},
			  name_{std::move(name)} {

		// Setup systems
		window_props props{};
		window_.reset(window::make(props));
		input_.reset(input::make());

		window_->set_ev_callback([this](ev &e) {
			application::on_event(e);
		});

		shader_.reset(new shader {"shaders/base.vs.glsl", "shaders/base.fs.glsl"});

		// region Setup rendering
		// Vertices
		float vertices[] = {
				// Positions           // Colors
				 0.0f,  0.5f, 0.0f,    0.5f,  0.5f, 0.0f, 1.0f,
				 0.0f, -0.5f, 0.0f,    0.5f,  0.0f, 0.5f, 1.0f,
				 0.5f,  0.0f, 0.0f,    0.0f,  0.5f, 0.5f, 1.0f,
				-0.5f,  0.0f, 0.0f,    0.5f,  0.5f, 0.5f, 1.0f,
		};

		unsigned int positions[]{
				0, 1, 2,
				0, 1, 3
		};

		// Vertex Array
		vao_.reset(vertex_array::make());
		vao_->bind();

		// Vertex Buffer
		vbo_.reset(vertex_buffer::make(vertices, sizeof(vertices)));
		vbo_->set_layout({
			{shader_data_t::vec3, "_pos",  },
			{shader_data_t::vec4, "_color",},
        });

		// Index Buffer
		ibo_.reset(index_buffer::make(positions, sizeof(positions) / sizeof(unsigned int)));
		ibo_->bind();

		// Link buffers to vertex array
		vao_->add_vertex_buffer(vbo_);
		vao_->add_index_buffer(ibo_);
		// endregion
	}

	void application::tick() {
	}

	void application::run() {
		VN_CORE_TRACE("Application is running!");

		while (is_running_) {
			render_command::clear_color(0.1f, 0.1f, 0.1f, 1.0f);
			render_command::clear();

			renderer::start_scene();

			vao_->bind();
			renderer::submit(vao_);

			renderer::end_scene();

			shader_->bind();
			render_command::draw_indexed(vao_);

			for (auto *layer : layers_) {
				layer->update();
			}

			window_->on_update();
		}

		VN_CORE_TRACE("Closing application;");
	}

	void application::on_event(ev &e) {
		VN_CORE_TRACE("Got event: {0}", e);

		ev_dispatcher dispatcher{&e};
		dispatcher.dispatch<window_close_ev>([this](window_close_ev &event) -> bool {
			this->on_window_close(event);
			return false;
		});

		for (auto it = layers_.end(); it != layers_.begin();) {
			(*--it)->handle_event(e);
			if (e.handled()) {
				break;
			}
		}
	}

	void application::on_window_close(window_close_ev &e) {
		this->is_running_ = false;
	}
}

