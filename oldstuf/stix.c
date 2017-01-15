/* stix shows a cable pattern from a .stix file.
 * The user can mark the current row because losing where you are in a cable
 * pattern is an awful thing. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <termbox.h>

#define MAX_W 100
#define MAX_H 50

#define len(a) (sizeof(a)/sizeof(a[0]))

static struct tb_cell *buffy;

long hardline;
int softline;
char filename[] = "test.stix";
char matrix[MAX_H][MAX_W];      // matrix[0] is hardline placement


void init_pattern() {
    FILE *fp = NULL;
    int lcount = 0;

    fp = fopen(filename, "r");
    while(fgets(matrix[lcount], MAX_W, fp)) {
        lcount++;
    }
    hardline = strtol(matrix[0], '\0', 10);
    if (hardline > MAX_H) {
        hardline = 0;
    }
    softline = (int)hardline;
}

void draw_all() {
    int rows = tb_height();
    int cols = tb_width();
    //NOTE Pretend that every possible file is smaller than the terminal
    tb_clear();
    int c = 0;
    int b = 1;
    for(int r = rows - 1; r >= 0; r--) {
        if(len(matrix[b]) > 0) {
            buffy[r] = matrix[b];
            b++;
        } else {
            break;
        }
    }
    
    for(int i = 0; i < rows; i++) {


    tb_select_output_mode(TB_OUTPUT_NORMAL);
    /* for min(pattern_size, term_size)
     * tb_put_cell(x, y, const struct tb_cell *cell)
     * */

    tb_present();
}

void move(int fromline, int toline) {
    // NOTE: Keep track of hardline colours as well w/ if clause
    // colour fromline in default colours
    // colour toline in softline colours
    tb_present();
}

void update_hardline() {
    int fromline = hardline;
    int toline = softline;
    // colour fromline in default colours
    // colour toline in hardline+softline colours
    hardline = toline; //NOTE: this shouldn't make it change afterwards
    // save hardline to file
    tb_present();
}

int main(int argc, char **argv) {
    int tb_code = tb_init();
    if (tb_code < 0) {
        fprintf(stderr, "termbox init failed, code: %d\n", tb_code);
        return -1;
    }

    hardline = 1; // counting from bottom of screen because knitting
    softline = 1; // counting from bottom of screen because knitting

    draw_all();

    struct tb_event ev;
    while(tb_poll_event(&ev)) {
        switch (ev.type) {
        case TB_EVENT_KEY:
            switch (ev.key) {
            case TB_KEY_ESC:
                /* print prompt for quit y/n on last row
                 * if y, tb_shutdown(); return 0; */
                break;
            case TB_KEY_ARROW_UP:
                move(softline, softline++);
                softline++;
                break;
            case TB_KEY_ARROW_DOWN:
                move(softline, softline--);
                softline--;
                break;
            case TB_KEY_ENTER:
                update_hardline();
                break;
            }
            break;
        case TB_EVENT_RESIZE:
            draw_all();
            break;
        }
    }
    /* Switch thingies:
     * ESC      quit (needs y/n)
     * UP       redraw 'softline' higher up unless highest
     * DOWN     redraw 'softline' lower down unless lowest
     * RETURN   draw 'hardline' here, save line number to file
     * PG_UP    redraw 'softline' highest up
     * PG_DN    redraw 'softline' lowest down
     * RESIZE   make resizing faces and redraw
     */
}
