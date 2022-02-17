#pragma once
#include "Singleton.h"
#include <exception>

class BaseComponent;
namespace dae {
	struct ComponentRegistrationException : public std::exception {
		ComponentRegistrationException(std::string& exceptionString) : m_ExceptionString{exceptionString}{};
		const char* what() const {
			return m_ExceptionString.c_str();
		}
	private:
		std::string m_ExceptionString;
	};


	class ComponentManager : public Singleton<ComponentManager>
	{
	public:
		ComponentManager();
		~ComponentManager();
		template<class TComponent>
		bool RegisterComponent() {
		
			try {
				if (!(TComponent::GetComponentID() <= m_RegisteredComponents) && TComponent::GetComponentID() == INT_MAX) {
					//Register new component
					TComponent::SetComponentID(m_RegisteredComponents);
					++m_RegisteredComponents; //Increase registered component counter
					return true;
				}
				else {
					std::string exceptionString = "Component ID: " + std::to_string(TComponent::GetComponentID()) + " is already registered!";
					throw ComponentRegistrationException( exceptionString );
				}
				return false;

			}
			catch(ComponentRegistrationException& e) {
				std::cout << e.what() << std::endl;
				return false;
			}
		
		}

	private:
		friend class Singleton<ComponentManager>;
		static int m_RegisteredComponents;


	};

}