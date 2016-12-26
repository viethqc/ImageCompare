#include "./include/sciter-x-window.hpp"
#include "Shlwapi.h"

static RECT wrc = { 100, 100, 800, 800 };

using namespace sciter;
using namespace dom;

class frame: public sciter::window
{
	
public:
	frame() : window( SW_MAIN | SW_ALPHA | SW_POPUP | SW_ENABLE_DEBUG, wrc)
	{
		this->load( WSTR("this://app/default.htm") ); 
		m_eRoot = dom::element::root_element(this->get_hwnd());

		eInputImage1 = m_eRoot.find_first("#image1");
		eInputImage2 = m_eRoot.find_first("#image2");
	}

private :
	dom::element m_eRoot;
	element eInputImage1;
	element eInputImage2;

	BEGIN_FUNCTION_MAP 
	FUNCTION_0("architecture", architecture);
	END_FUNCTION_MAP

	int architecture() 
	{  
		// this function is here just for the demo purposes,
		// it shows native function callable from script as view.architecture();
		#if defined(TARGET_32)
			return 32;
		#elif defined(TARGET_64)
			return 64;
		#endif
	}

	virtual bool on_event (HELEMENT he, HELEMENT target, BEHAVIOR_EVENTS type, UINT_PTR reason ) 
	{
		if (type == BUTTON_CLICK)
		{
			value vImage1 = eInputImage1.get_value();
			sciter::string strImage1 =  vImage1.to_string();

			value vImage2 = eInputImage2.get_value();
			sciter::string strImage2 =  vImage2.to_string();

			if (PathFileExists(strImage1.data()) == false)
			{
				MessageBox(this->get_hwnd(), L"Image 1 path not exist", 0, 0);
				return false;
			}

			if (PathFileExists(strImage2.data()) == false)
			{
				return false;
				MessageBox(this->get_hwnd(), L"Image 2 path not exist", 0, 0);
			}


			int a = 0;
		}
		return false;
	}
};

#include "resources.cpp" // packed /res/ folder

int uimain(std::function<int()> run ) {

	sciter::archive::instance().open(aux::elements_of(resources)); // bind resources[] (defined in "resources.cpp") with the archive

	frame *pwin = new frame();

	// note: this:://app URL schema is dedicated to the sciter::archive content associated with the application
	 
	pwin->expand();
	  
	return run(); 
}