#include <iostream>
#include <vector>
#include <SDL.h>
#include <ctime>
#include <fstream>
#include <SDL_image.h>

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

SDL_Texture* loadTexture(string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr)
        {
            cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

struct food
{
    int fX;
    int fY;
    int fW;
    int fH;
    SDL_Texture* texture;
    food(SDL_Texture* tex = NULL)
    {
        fW = 20;
        fH = 20;
        fX = (rand() % 32) * 20;
        fY = (rand() % 24) * 20;
        tex = texture;
    }
    void draw_food(SDL_Renderer* renderer)
    {
        SDL_Rect F;
        F.w = fW;
        F.h = fH;
        F.x = fX;
        F.y = fY;
        if (texture != NULL)
        {
            SDL_RenderCopy(renderer, texture, NULL, &F);
        }
        SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
        SDL_RenderFillRect(renderer, &F);
    }
    void GEN_F()
    {
        fX = (rand() % 32) * 20;
        fY = (rand() % 24) * 20;
    }
};

struct body
{
    int Xb;
    int Yb;
    int Wb;
    int Hb;
    SDL_Texture* texture;
    body(int _x, int _y, int _w, int _h, SDL_Texture* tex = NULL)
    {
        Xb = _x;
        Yb = _y;
        Wb = _w;
        Hb = _h;
        texture = tex;
    }
    void draw_body(SDL_Renderer* renderer, int prevX, int prevY, int rotation, bool head = true) {
        SDL_Rect BODY;
        BODY.w = Wb;
        BODY.h = Hb;
        BODY.y = Yb;
        BODY.x = Xb;
        if (head == false) {
            // Calculate the direction of movement for this body segment
            int deltaX = prevX - Xb;
            int deltaY = prevY - Yb;
            if (deltaX > 0) {
                // Moving to the right
                rotation = 0;
            }
            else if (deltaX < 0) {
                // Moving to the left
                rotation = 180;
            }
            else if (deltaY > 0) {
                // Moving downwards
                rotation = 90;
            }
            else if (deltaY < 0) {
                // Moving upwards
                rotation = -90;
            }
        }

        if (texture != NULL) {
            SDL_RenderCopyEx(renderer, texture, nullptr, &BODY, rotation, nullptr, SDL_FLIP_NONE);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 200, 0, 200, 255);
            SDL_RenderFillRect(renderer, &BODY);
        }
    }
};

class snake
{
public:
    int speed;
    vector <body> BODY;
    enum Direction { UP, DOWN, LEFT, RIGHT };
    Direction direct;
    food FOOD;
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
    // khoi tao ran
    snake(int SPEED = 1, vector <body> initbody = { body(12 * 20,16 * 20,20,20) })
    {
        speed = SPEED;
        BODY = initbody;
        //chen anh dau va than

    }
    // cap nhat huong di chuyen
    void update()
    {
        headTexture = loadTexture("headup.jpg", renderer);
        if (headTexture == NULL)
            cout << "Failed to load up!!!!!!!!!!!!!!!!!!!!!";
        bodyTexture = loadTexture("body.jpg", renderer);
        for (int i = 0; i < (int)BODY.size(); i++)
        {
            if (i == 0)
                BODY[i].texture = headTexture;
            else
                BODY[i].texture = bodyTexture;
        }
        // Save the current position of the head
        int prevX = BODY[0].Xb;
        int prevY = BODY[0].Yb;
        int nextX;
        int nextY;

        // cap nhat laij huong cua dau de anh huong theo
        switch (direct)
        {
        case UP:
            BODY[0].Yb -= 20;
            break;
        case DOWN:
            BODY[0].Yb += 20;
            break;
        case LEFT:
            BODY[0].Xb -= 20;
            break;
        case RIGHT:
            BODY[0].Xb += 20;
            break;
        }

        // Move the rest of the body segments to follow the head
        for (int i = 1; i < BODY.size(); i++)
        {
            nextX = BODY[i].Xb;
            nextY = BODY[i].Yb;
            BODY[i].Xb = prevX;
            BODY[i].Yb = prevY;
            prevX = nextX;
            prevY = nextY;
        }
    }

    // movement
    void input_dir(SDL_Event& events)
    {
        if (events.type == SDL_KEYDOWN)
        {
            switch (events.key.keysym.sym)
            {
            case SDLK_LEFT:
                if (direct != RIGHT)
                    direct = LEFT;
                cout << "Direction left" << endl;
                break;
            case SDLK_RIGHT:
                if (direct != LEFT)
                    direct = RIGHT;
                cout << "Direction Right" << endl;
                break;
            case SDLK_UP:
                if (direct != DOWN)
                    direct = UP;
                cout << "Direction up" << endl;
                break;
            case SDLK_DOWN:
                if (direct != UP)
                    direct = DOWN;
                cout << "Direction down" << endl;
                break;
            }
        }
    }

    void BORDERCHECK(bool& Q)
    {
        if (BODY[0].Xb < 0 || BODY[0].Xb >= 640 || BODY[0].Yb < 0 || BODY[0].Yb >= 480)
            Q = true;
    }

    void EATCHECK(int prex, int prey)
    {
        cout << "food x " << FOOD.fX << " y " << FOOD.fY << endl;
        cout << "snake x " << BODY[0].Xb << " y " << BODY[0].Yb << endl;
        cout << BODY.size() << endl;
        if (BODY[0].Xb == FOOD.fX && BODY[0].Yb == FOOD.fY)
        {
            cout << "ANNNNN" << endl;
            body newBody(prex, prey, 20, 20, bodyTexture);
            BODY.push_back(newBody);//chen them anh than vao body
            SDL_Delay(200);
            FOOD.GEN_F();
        }
    }
};

Uint32 lastEventTime = 0;

int main(int argc, char* args[])
{
    // create window
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

    // init map ( no longer need )
//    char MAP[24][32];
//    input_map(MAP);
    // main loop

    srand(time(NULL));


    SDL_Texture* backgroundTexture = loadTexture("backgr.jpg", renderer);
    SDL_Texture* appleTexture = loadTexture("applee.png", renderer);//chen anh qua tao

    snake SNAKE;
    food FOOD(appleTexture);
    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        SDL_RenderClear(renderer); // Clear the renderer
        if (backgroundTexture != nullptr)
            // load anh backgr
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        SDL_Rect appleRect;
        appleRect.x = SNAKE.FOOD.fX;
        appleRect.y = SNAKE.FOOD.fY;
        appleRect.w = 20;
        appleRect.h = 20;
        if (appleTexture != NULL)
            SDL_RenderCopy(renderer, appleTexture, NULL, &appleRect);
        //SNAKE.FOOD.draw_food(renderer);
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastEventTime >= 1)
        {
            while (SDL_PollEvent(&e) != 0)
            {

                if (e.type == SDL_QUIT)
                    quit = true;
                // quit = escape
                const Uint8* keys = SDL_GetKeyboardState(nullptr);
                if (keys[SDL_SCANCODE_ESCAPE])
                    quit = true;
                SNAKE.input_dir(e);
            }
            lastEventTime = currentTime;
        }


        SNAKE.BORDERCHECK(quit);    //border
        SNAKE.update();  //movement

        //previous coordinate
        int prex = SNAKE.BODY[SNAKE.BODY.size() - 1].Xb;
        int prey = SNAKE.BODY[SNAKE.BODY.size() - 1].Yb;
        SNAKE.EATCHECK(prex, prey);
        int rotation = 0;
        switch (SNAKE.direct) {
        case snake::UP:
            rotation = -90;
            break;
        case snake::DOWN:
            rotation = 90;
            break;
        case snake::LEFT:
            rotation = 180;
            break;
        case snake::RIGHT:
            rotation = 0;
            break;
        }
        // Render each body segment with its respective rotation
        for (int i = 0; i < SNAKE.BODY.size(); i++)
            SNAKE.BODY[i].draw_body(renderer, i == 0 ? 0 : SNAKE.BODY[i - 1].Xb, i == 0 ? 0 : SNAKE.BODY[i - 1].Yb, rotation, i == 0);
        SDL_RenderPresent(renderer);

        SDL_Delay(150);
    }
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
