#pragma once
#include "../../Common.h"
#include "../Texture.h"

namespace Bitz
{
	namespace GFX
	{
		class GraphicsManager;
		class RenderEngine;

		namespace Drawables
		{
			/// <summary>
			/// This interface defines an object that can be rendered by the graphics manager
			/// </summary>
			class IDrawable
			{
			public:
				friend GraphicsManager;
				friend RenderEngine;
				enum RenderMode
				{
					TwoD, ThreeD
				};
				virtual ~IDrawable()
				{
					if (_VertArray != nullptr)delete[] _VertArray;
					if (_ColArray != nullptr)delete[] _ColArray;
					if (_TexArray != nullptr)delete[] _TexArray;
					if (_NormArray != nullptr)delete[] _NormArray;
				}
				virtual void PopulateVertArray(float_t * vertArray, int32_t * startPosition) = 0;
				virtual void PopulateColArray(float_t * colArray, int32_t * startPosition) = 0;
				virtual void PopulateTexArray(float_t * texArray, int32_t * startPosition) = 0;
				virtual void PopulateNormArray(float_t * normArray, int32_t * startPosition) = 0;
				virtual uint32_t GetVertCount() const = 0;
				virtual void SetTexture(Texture* newTexture)
				{
					_Texture = newTexture;
				}
				virtual Texture * GetTexture() const
				{
					return _Texture;
				}

			protected:
				float_t * _VertArray = nullptr;
				float_t * _ColArray = nullptr;
				float_t * _TexArray = nullptr;
				float_t * _NormArray = nullptr;
				int32_t _VertCount = 0;
				RenderMode _RenderMode;
				Texture * _Texture = nullptr;
			};
		}
	}
}