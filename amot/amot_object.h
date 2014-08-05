#include "amot_base.h"

namespace amot
{
	//interface: object
	//newable and disposable 
	class AMOT_API IObject
	{
	public:
		//default <constructor>
		virtual void New() = 0;

		//default <destructor>
		virtual bool Dispose() = 0;
	};
}