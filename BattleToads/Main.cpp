#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#include "MathGeoLib/include/MathGeoLib.h"

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )



enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char ** argv)
{
	ReportMemoryLeaks();
	float4 vector;
	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	vector.w = 0;
	float4 vector2 = vector.Abs();
	


	
	
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:
		
			LOG_GLO("Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG_GLO("Application Init --------------");
			if (App->Init() == false)
			{
				LOG_GLO("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG_GLO("Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG_GLO("Application Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG_GLO("Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG_GLO("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	RELEASE( App);
	LOG_GLO("Bye :)\n");
	return main_return;
}