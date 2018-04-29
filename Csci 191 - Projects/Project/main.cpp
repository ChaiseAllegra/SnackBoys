#pragma once

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include <GLScene.h> //change

#include <stdlib.h>
#include<timer.h>
#include <iostream>
#include <windows.h>		// Header File For Windows

using namespace std;
timer* menu= new timer();
bool mainMenChoice=false;


HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLScene *Scene = new GLScene();


/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE KILL GL WINDOW
/////////////////////////////////////////////////////////////////////////////////////////////////
GLvoid KillGLWindow()								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE CREATE GL WINDOW
/////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle= WS_POPUP;			// must handle Gsync situations: Windows Style
		ShowCursor(FALSE);									// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);
					// Sets Keyboard Focus To The Window
	Scene->resizeGLScene(width, height);			// Set Up Our Perspective GL Screen

	if (!Scene->initGL())							// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}


	return TRUE;									// Success
}



/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE WINDOW PROCEDURE
/////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
   // Scene->windMsg(hWnd,uMsg,wParam,lParam,keys);
//    levelA->windMsg(hWnd,uMsg,wParam,lParam,keys);

	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE

			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
                                                    // LoWord=Width, HiWord=Height
			//Scene->ReSizeGLScene(GetSystemMetrics(SM_CXSCREEN),HIWORD(lParam));


			Scene->resizeGLScene(LOWORD(lParam),HIWORD(lParam));
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										THE WINMAIN
/////////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
    menu->start();
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	int	fullscreenWidth  = GetSystemMetrics(SM_CXSCREEN);
    int	fullscreenHeight = GetSystemMetrics(SM_CYSCREEN);
    //cout<<fullscreenWidth<<", "<<fullscreenHeight<<endl;

	// Ask The User Which Screen Mode They Prefer
	/*if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}*/

	// Create Our OpenGL Window
	if (!CreateGLWindow("Game Engine Lesson 01",fullscreenWidth,fullscreenHeight,256,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			//menu[0]: landing page
			//menu[1]: main menu
			//menu[2]: game rules
			//menu[3]: play Game
			//menu[4]: in game menu
			//menu[5]: controls
			//menu[6]: game is won
			Scene->drawGLScene2(keys);
            SwapBuffers(hDC);

            if(keys[VK_RETURN] && Scene->menu[0]==true && menu->getTicks() > 150)
            {
                Scene->menu[1]=true;
                menu->reset();
            }

            if(keys['H']&&Scene->menu[1]==true)//info page
            {
                			    //cout<<"in here3"<<endl;
            	Scene->menu[1]=false;
                Scene->menu[2]=true;

            }
            if ( keys[VK_ESCAPE]&&Scene->menu[2]==true)	//takes you from info page to main menu
			{
				Scene->menu[2]=false;
                Scene->menu[1]=true;

			}
            if(keys['N']&&Scene->menu[1]==true)
            {
            	Scene->menu[1]=false;
            	Scene->menu[3]=true;

            }
             if(keys['I']&&Scene->menu[1]==true)
            {
            	Scene->menu[1]=false;
            	Scene->menu[5]=true;

            }
            if ( keys[VK_ESCAPE]&&Scene->menu[5]==true)	//takes you from info page to main menu
			{
				Scene->menu[5]=false;
                Scene->menu[1]=true;

			}
            if(keys['P']&&Scene->menu[1]==true)//quit from the main menu
                done=TRUE;


            if(keys[VK_ESCAPE]&&Scene->menu[3]==true)//brings up in game menu
            	Scene->menu[4]=true;

            else if(keys[VK_ESCAPE]&&Scene->menu[4]==true)// switches from in game menu to the game
            		Scene->menu[4]=false;
            //Main menu Navigation
            if(Scene->menu[1])
            {
                if((keys['A']||keys['J'])&&Scene->mainMenPos>0&&menu->getTicks()>150)
                {
                    Scene->mainMenPos--;
                    menu->reset();
                }
                if((keys['D']||keys['L'])&&Scene->mainMenPos<3&&menu->getTicks()>150)
                {
                    Scene->mainMenPos++;
                    menu->reset();
                }
                if(keys['E']||keys['O']&&menu->getTicks()>150)
                {
                    mainMenChoice=true;
                    Scene->menu[1]=false;
                    menu->reset();
                }
                if(mainMenChoice)
                {
                    if(Scene->mainMenPos==0)
                        Scene->menu[3]=true;
                    if(Scene->mainMenPos==1)
                        Scene->menu[2]=true;
                    if(Scene->mainMenPos==2)
                        Scene->menu[5]=true;
                    if(Scene->mainMenPos==3)
                        done=true;
                    mainMenChoice=false;
                    Scene->mainMenPos=0;
                }
                //cout<<Scene->mainMenPos<<endl;
<<<<<<< HEAD
=======
            }
            if(Scene->menu[6])
            {
                if(keys['E']||keys['O'])
                {
                    Scene->menu[6]=false;
                    Scene->menu[3]=false;
                    Scene->menu[1]=true;
                    Scene->plyScore=0;
                    Scene->ply2Score=0;
                }
>>>>>>> 8c479ba7c1100afb4c51651aee8402394d638c23
            }
            if(Scene->menu[4]==true)//Scene->pauseMenu)
            {
               if(keys['S']&&menu->getTicks()>150)
               {
                   menu->reset();
                   if(Scene->menuPos>0)
                        Scene->menuPos-=1;
               }
               if(keys['W']&&menu->getTicks()>150)
               {
                   menu->reset();
                    if(Scene->menuPos<2)
                        Scene->menuPos++;
               }
               if(keys['E'])
                    Scene->pauseChoice=true;
               if(Scene->pauseChoice&&Scene->menuPos==0)
                    done=true;
            }

            if(keys[VK_RETURN]&&Scene->menu[4]==true)//quit the game from in game menu
                done=TRUE;

            if(Scene->menu[0]==true&&keys['Q']==true)									// Not Time To Quit, Update Screen
			    Scene->menu[3]=true;
			 					// Swap Buffers (Double Buffering)
			if(keys[VK_END])
                done=TRUE;

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("Game Engine Lesson 01",fullscreenWidth,fullscreenHeight,256,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
      }


	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
