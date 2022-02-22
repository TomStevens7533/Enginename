#pragma once

#include "BaseComponent.h"
#include "Texture2D.h"
#include <glm/glm.hpp>

namespace dae {
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent();
		~RenderComponent();

		inline static const int GetComponentID() { return m_ComponentContext.m_ComponentID; }
		inline static void SetComponentID(int newID) {
			m_ComponentContext.m_ComponentID = newID;
			m_ComponentContext.isRegistered = true;
		}
		void Render() const override;
		void Update() override;
		void LateUpdate() override;
		void SetPos(const glm::vec2 pos);
		void SetData(std::shared_ptr<void> newData);

	private:
		static ComponentContext m_ComponentContext;
		std::shared_ptr<void> m_DataToRender;
		glm::vec2 m_Position = {0,0};
	};



}


