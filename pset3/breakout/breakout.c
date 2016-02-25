//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// padding
#define WIN_PADDING 10
#define OBJ_PADDING 2

// brick size
#define B_WIDTH 38 
#define B_HEIGHT 15 

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle
#define P_HEIGHT 12
#define P_WIDTH 80
#define PADDLE_Y 500
#define PADDLE_X HEIGHT - (2*WIN_PADDING) + OBJ_PADDING

//Ball movement

#define BALL_DX      0.03
#define BALL_VEL     BALL_DX*BALL_DX*2
#define BALL_DY(dx) (sqrt(BALL_VEL - (dx*dx)))

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);
    double bdx = BALL_DX;
    double bdy = BALL_DY(BALL_DX);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    GObject collisionObject;
    waitForClick();

    while (lives > 0 && bricks > 0)
    {
        GEvent eMouse = getNextEvent(MOUSE_EVENT);
        if (eMouse != NULL)
        {
            if (getEventType(eMouse) == MOUSE_MOVED)
            {
                int x = getX(eMouse) - getWidth(paddle) / 2;
                setLocation(paddle, x, PADDLE_Y);
            }
            
        }
              
        move(ball,bdx,bdy);
        if((getX(ball) + getWidth(ball) >= WIDTH || getX(ball) <= 0))
        {
            bdx *= -1;
        }
        else if(getY(ball) <= 0)
        {
            bdy *= -1;
        }
        else if ((getY(ball) + getHeight(ball) >= HEIGHT))
        {
            lives--;
            setLocation(ball, (WIDTH/2) - RADIUS, (HEIGHT / 2) - RADIUS);
            setLocation(paddle,PADDLE_X, PADDLE_Y);
            bdx = BALL_DX;
            bdy = BALL_DY(BALL_DX);
            waitForClick();
        }

        collisionObject = detectCollision(window, ball);

        if (collisionObject != NULL && strcmp(getType(collisionObject), "GRect") == 0)
        {
            bdy *= -1;
            if (collisionObject != paddle)
            {
                removeGWindow(window, collisionObject);
                bricks--;
                points++;
                updateScoreboard(window, label, points);
                printf("bricks: %d points: %d\n", bricks, points);
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    string brickColors[] = {"RED", "ORANGE", "YELLOW", "BLUE", "GREEN"};
    int colorIndex = 0;

    int lastX = (B_WIDTH * (COLS - 1)) + WIN_PADDING;
    int lastY = (B_HEIGHT * (ROWS - 1)) + WIN_PADDING;
    
    for (int y = WIN_PADDING; y <= lastY; y += B_HEIGHT)
    {
        for (int x = WIN_PADDING; x <= lastX; x += B_WIDTH)
        {
            GRect brick = newGRect(x + OBJ_PADDING, y + OBJ_PADDING, B_WIDTH-(2 * OBJ_PADDING), B_HEIGHT-(2 *          OBJ_PADDING));
            setColor(brick, brickColors[colorIndex]);
            setFilled(brick, true);
            add(window, brick);
        }
        colorIndex++;
    }

}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{

    int x = (WIDTH / 2) - RADIUS;
    int y = (HEIGHT / 2) - RADIUS;

    GOval circle = newGOval(x, y, RADIUS*2, RADIUS*2);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    
    
    add(window, circle);

    return circle;

}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect((WIDTH/2) - (80 / 2), 500, 80, 12);
    add(window, paddle);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label,"DejaVuSansMono-40");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    setColor(label, "GRAY");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
