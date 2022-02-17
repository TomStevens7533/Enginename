#pragma once
#include <limits.h>
namespace dae {
	struct ComponentContext
	{
		bool isRegistered;
		int m_ComponentID;
	};

	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;

		virtual void Render() const = 0;



	protected:
		int m_RegisteredToID = INT_MAX;
	};


}
