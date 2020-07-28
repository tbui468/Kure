#pragma once

#include "Kure/Log.h"

namespace Kure {

	enum class ShaderDataType {
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		MatF3, MatF4, 
		Bool
	};

	static uint32_t GetShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:  return sizeof(float);
		case ShaderDataType::Float2: return sizeof(float) * 2;
		case ShaderDataType::Float3: return sizeof(float) * 3;
		case ShaderDataType::Float4: return sizeof(float) * 4;
		case ShaderDataType::Int:   return sizeof(int);
		case ShaderDataType::Int2:  return sizeof(int) * 2;
		case ShaderDataType::Int3:  return sizeof(int) * 3;
		case ShaderDataType::Int4:  return sizeof(int) * 4;
		case ShaderDataType::MatF3: return sizeof(float) * 3 * 3;
		case ShaderDataType::MatF4: return sizeof(float) * 4 * 4;
		case ShaderDataType::Bool:  return 1;
		}
		KR_CORE_ASSERT(false, "Invalid ShaderDataType");
		return 0;
	}


	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized = false;

		BufferElement(ShaderDataType type, const std::string& name) :
			Name(name), Type(type), Size(GetShaderDataTypeSize(type)), Offset(0) {}

		uint32_t GetElementCount() const {
			switch (Type) {
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Int:   return 1;
			case ShaderDataType::Int2:  return 2;
			case ShaderDataType::Int3:  return 3;
			case ShaderDataType::Int4:  return 4;
			case ShaderDataType::MatF3: return 3 * 3;
			case ShaderDataType::MatF4: return 4 * 4;
			case ShaderDataType::Bool:  return 1;
			}

			KR_CORE_ASSERT(false, "Invalid ShaderDataType");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& layout) : m_Elements(layout) {
			CalculateOffsetAndStride();
		}
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		inline uint32_t GetStride() const { return m_Stride; }
	private:
		void CalculateOffsetAndStride() {
			for (BufferElement& element : m_Elements) {
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		~VertexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		~IndexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
		static IndexBuffer* Create(unsigned int* indices, uint32_t count);
	};

}

