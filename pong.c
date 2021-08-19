#include "pong.h"

uint16 pad_pos_y = 2;

uint32 score_count = 0;

static void init_game()
{
    uint8 b = 0;

    draw_string(120, 13, BRIGHT_CYAN, "PONG GAME");
    draw_rect(100, 4, 120, 25, BLUE);
    draw_string(10, 50, BRIGHT_MAGENTA, "HOW TO PLAY");
    draw_rect(2, 40, 235, 80, BROWN);
    draw_string(10, 70, BRIGHT_RED, "ARROW KEY UP");
    draw_string(30, 80, WHITE, "TO MOVE BOTH PADS UP");
    draw_string(10, 90, BRIGHT_RED, "ARROW KEY DOWN");
    draw_string(30, 100, WHITE, "TO MOVE BOTH PADS DOWN");
    draw_string(60, 160, BRIGHT_GREEN, "PRESS ENTER TO START");
#ifdef VIRTUALBOX
    sleep(10);
#endif
    while (1)
    {
        b = get_input_keycode();
        sleep(5);
        if (b == KEY_ENTER)
            break;
        b = 0;
    }
    clear_screen();
}

static void update_score_count()
{
    char str[32];

    itoa(score_count, str);
    draw_string(150, 2, WHITE, str);
}

static void lose()
{
    uint8 b = 0;
    char str[32];

    itoa(score_count, str);
    clear_screen();
    draw_string(120, 15, BRIGHT_GREEN, "NICE PLAY");
    draw_string(125, 45, WHITE, "SCORE");
    draw_string(180, 45, WHITE, str);
    draw_string(45, 130, YELLOW, "PRESS ENTER TO PLAY AGAIN");

#ifdef VIRTUALBOX
    sleep(10);
#endif
    while (1)
    {
        b = get_input_keycode();
        sleep(5);
        if (b == KEY_ENTER)
            break;
        b = 0;
    }
    score_count = 0;
    clear_screen();
    pong_game();
}

void move_pads()
{
    uint8 b;

    fill_rect(0, pad_pos_y, PAD_WIDTH, PAD_HEIGHT, YELLOW);
    fill_rect(PAD_POS_X, pad_pos_y, PAD_WIDTH, PAD_HEIGHT, YELLOW);

    b = get_input_keycode();
    if (b == KEY_DOWN)
    {
        if (pad_pos_y < VGA_MAX_HEIGHT - PAD_HEIGHT)
            pad_pos_y = pad_pos_y + PAD_SPEED;
        fill_rect(0, pad_pos_y, PAD_WIDTH, PAD_HEIGHT, YELLOW);
        fill_rect(PAD_POS_X, pad_pos_y, PAD_WIDTH, PAD_HEIGHT, YELLOW);
    }
    else if (b == KEY_UP)
    {
        if (pad_pos_y >= PAD_WIDTH)
            pad_pos_y = pad_pos_y - PAD_SPEED;
        fill_rect(0, pad_pos_y, PAD_WIDTH, PAD_HEIGHT, YELLOW);
        fill_rect(PAD_POS_X, pad_pos_y, PAD_WIDTH, PAD_HEIGHT, YELLOW);
    }
#ifdef VIRTUALBOX
    sleep(1);
#endif
}


void pong_game()
{
    uint16 rect_pos_x = RECT_SIZE + 20;
    uint16 rect_pos_y = RECT_SIZE;
    uint16 rect_speed_x = RECT_SPEED_X;
    uint16 rect_speed_y = RECT_SPEED_Y;

    init_game();

    while (1)
    {
        rect_pos_x += rect_speed_x;
        rect_pos_y += rect_speed_y;

        if (rect_pos_x - RECT_SIZE <= PAD_WIDTH + 1)
        {
            if ((rect_pos_y > 0 && rect_pos_y < pad_pos_y) || 
                (rect_pos_y <= VGA_MAX_HEIGHT && rect_pos_y > pad_pos_y + PAD_HEIGHT))
            {
                lose();
            }
            else
            {
                rect_speed_x = -rect_speed_x;
                rect_pos_x = PAD_WIDTH + RECT_SIZE;
                score_count++;
            }
        }
        else if (rect_pos_x + RECT_SIZE >= PAD_POS_X + RECT_SIZE - 1)
        {
            if ((rect_pos_y > 0 && rect_pos_y < pad_pos_y) || 
                (rect_pos_y <= VGA_MAX_HEIGHT && rect_pos_y > pad_pos_y + PAD_HEIGHT) || 
                (rect_pos_y + RECT_SIZE > 0 && rect_pos_y + RECT_SIZE < pad_pos_y))
            {
                lose();
            }
            else
            {
                rect_speed_x = -rect_speed_x;
                rect_pos_x = PAD_POS_X - RECT_SIZE;
                score_count++;
            }
        }

   
        if (rect_pos_y - RECT_SIZE <= 0)
        {
            rect_speed_y = -rect_speed_y;
            rect_pos_y = RECT_SIZE;
        }
        else if(rect_pos_y + RECT_SIZE > VGA_MAX_HEIGHT + RECT_SIZE)
        {
            rect_speed_y = -rect_speed_y;
            rect_pos_y = VGA_MAX_HEIGHT - RECT_SIZE;
        }

  
        clear_screen();

        move_pads();
      
        update_score_count();
       
        fill_rect(rect_pos_x - RECT_SIZE, rect_pos_y - RECT_SIZE, RECT_SIZE, RECT_SIZE, WHITE);
        
        sleep(1);
    }
}
