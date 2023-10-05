#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

enum chipsAhoy { Red, Yellow, Blue, Green, Black };
enum vanillaOreo { Skip, Reverse, DrawTwo, Wild, WildDrawFour };

#define CardBmpDim 4096
#define Scale 0.17
#define Spacing 17
#define clientWidth 1280
#define clientHeight 720
#define cardWidth (CardBmpDim / 10)*Scale
#define cardHeight (CardBmpDim / 7)*Scale