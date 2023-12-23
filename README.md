# cocosParallax

SMALL EXPLANATION:


This code is a simulation of a horizontally parallax scene done in cocosd2-x engine for C++.

The game should be started and the main aspect of the game should containt:
3 layers which have parallax effect, a character on the screen and a UI button that
when pressed will make the character jump.

3 layers should be split into:
background - the data behind the character on the screen
focus - the data in the same layer level as the character
foreground - the data in front of the character on the screen

The parallax scene is based mostly on the functionality that the further the layer is
the slower it's animation occurs, even tho there's no animation going on,
just an image being moved in a time occurency.

The parallax scene can be used to simulate visual movement and dynamic movements.


LOGIC BEHIND THE GAME:

This game is just a visual presentation of the parallax system.

There is no main goal, just to enjoy the scene! :)

The main character of the game is a frog character that watches the scene move around him!
The frog can get scared by the squirrel that appears from the bushes so he can jump from
scare!!!

PROGRAMING LOGIC:

The main idea was to create a optimized, code efficient, readable and maintainable code.
The main code is started on the main node of the game: GameScene. The GameScene is a coupled 
version of a node and the "GameManager". The GameScene is the parent of all the nodes on the 
scene and the holder of all sub systems that control the game pipeline. The main goal of the 
GameScene is to instantiate objects and nodes. Instantiated objects may be different controllers,
different managers, etc.

The GameScene creates a few controllers that are tied together by the same interface.

IController - interface that is the main skeleton for every controller type, not of a big usage here, but is scalable and modular for use.

CharacterController - controls the character that is passed to him, in our situation it just reacts to the UI button pressed and by that the trigger
event makes the character controller react to that input and trigger the character to jump.

InputController - controls and registers all the input that come from different sources - dragging, pressing, pressing specific buttons, etc.

ParallaxController - is a controller that controls the parallax layers on the scene. There are 3 main ParallaxLayers that are being monitored.
The ParallaxController reacts to the screen dragged by moving for a certain amount the screen in a horizontal direction. 
The ParallaxController adds sprites to specific layers. If the z order has been provided, it's inserted on a specific Z order on the target layer,
if not it's set on the last place. The parallax controller makes sure the sprite is well positioned on the layer and seen(through scaling and anchoring).

UIController - is a controller that controls the objects on the UI layer. He holds a vector of UI elements that can be resized and repositioned depending
on the aspect ratio or resolution. 



In the current code there are 2 singleton classes:
AssetManagerSingleton - receives the base path for the textures folder in which he should look. He holds a cache of sprites he loads in a LRU principle, 
so if we try to load the same assets, we will have them already cached for a certain amount of time. For additional checks, he can check if a file 
exists(can be used elsewhere beside the assets).

GameSettings - singleton used for mostly getting some data factors from the current game such as scaled values, aspect ratio values,  etc. mostly
dynamic calculated variables for device specific game environment.



IResizableUI - interface that is the main skeleton for every button in the UI layer. Not incredibly usefull here, but can lead to scalable options,
can be used to couple ui elements where needed. Like this the systems that use the buttons don't need to know a lot of who are they communicating with,
but they know they can have a valid object who knows who to adress or be adressed.

CustomUIButton - is a buttom that mostly is used as a cocosd2-x button with the main difference that it loads the sprite directly and it inherits the IResizableUI,
so it can be resized through the UIController(since he controlls the UI layer).


GameConstants and GameEvents are static data holders that offer the system constant information about some specific game related stuff like paths, layers, resolution sizes, specific data events, etc.



DOD:

The main goal of the code is in my opinion satisfied. The parallax scene is working and scrollable horizontally(by dragging it). The scene has 3 parallax layers: background, focus and foreground which have their speed and logic. The UI button is situated in the UI Layer and it has a functionality to trigger the jump event on the character.

The CMake is updated to work with multiple platforms. 


ISSUES AND PROBLEMS:

The problem I was facing was mostly with the android studio setup for cocosd2-x where I spent most of my time and finally wasn't able to test it directly through the android studio. By that I couldn't also test the resolutions and scales of different devices, so I improvised and created a sub scaleable system inside the system that would take the original designed resolution and scales objects in the specific calculated manner.







Thank you for your time. :)

It was a nice task! 