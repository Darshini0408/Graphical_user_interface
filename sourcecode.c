#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
// Struct to represent list item
typedef struct {
char *name;
void (*callback)(void); // Function pointer for callback
} ListItem;
// Function to display a list of items and handle user selection
void displayList(const char *title, ListItem *items, int itemCount) {
initscr();
cbreak();
noecho();
keypad(stdscr, TRUE);
printw("%s\n\n", title);
for (int i = 0; i < itemCount; ++i) {
printw("%d. %s\n", i + 1, items[i].name);
}
printw("\nSelect an option (1-%d): ", itemCount);
refresh();
int choice = getch() - '0';
if (choice < 1 || choice > itemCount) {
printw("\nInvalid option\n");
refresh();
getch();
endwin();
return;
}
items[choice - 1].callback();
endwin();
}
// Example callback functions
void callbackA() {
printw("\nOption A selected\n");
refresh();
getch();
}
void callbackB() {
printw("\nOption B selected\n");
refresh();
getch();
}
// Struct to represent table data
typedef struct {
char *title;
char **headers;
char ***data;
int rowCount;
int colCount;
int *sizes;
void (*callback)(void); // Callback function }
Table;
// Function to display a table
void displayTable(Table *table) {
initscr();
cbreak();
noecho();
keypad(stdscr, TRUE);
printw("%s\n\n", table->title);
for (int j = 0; j < table->colCount; ++j) {
printw("%-*s", table->sizes[j], table->headers[j]);
}
printw("\n");
for (int j = 0; j < table->colCount; ++j) {
for (int i = 0; i < strlen(table->headers[j]); ++i) {
printw("-");
}
if (table->sizes != NULL) {
for (int i = 0; i < table->sizes[j] - strlen(table->headers[j]); ++i) {
printw("-");
}
}
printw("-+-");
}
printw("\n");
for (int i = 0; i < table->rowCount; ++i) {
for (int j = 0; j < table->colCount; ++j) {
printw("%-*s", table->sizes[j], table->data[i][j]);
}
printw("\n");
}
table->callback();
refresh();
getch();
endwin();
}
// Example callback function for table
void tableCallback() {
printw("\nTable callback executed\n");
refresh();
getch();
// Struct to represent guided prompt option
typedef struct {
char *name;
char *description;
char **options;
int optionCount;
} Option;
// Function to display a guided prompt
void displayGPrompt(const char *title, const char *message, Option
*options, int optionCount) {
initscr();
cbreak();
noecho();
keypad(stdscr, TRUE);
printw("%s\n\n", title);
printw("%s\n", message);
for (int i = 0; i < optionCount; ++i) {
printw("%d. %s\n", i + 1, options[i].name);
if (options[i].description != NULL) {
printw(" %s\n", options[i].description);
}
for (int j = 0; j < options[i].optionCount; ++j) {
printw(" %s\n", options[i].options[j]);
}
}
refresh();
int choice = getch() - '0';
if (choice < 1 || choice > optionCount) {
printw("\nInvalid option\n");
refresh();
getch();
endwin();
return;
}
endwin();
}
int main() {
// List example
ListItem listItems[] = {
{"Option A", callbackA},
{"Option B", callbackB},
};
displayList("This is a list", listItems, sizeof(listItems) / sizeof(listItems[0]));
// Table example
char *headers[] = {"a", "b", "c"};
char *data[][3] = {{"hello", "this", "is"}, {"a", "cool", "test"}, {"tables", "are", "fun"}};
int rowCount = sizeof(data) / sizeof(data[0]);
int colCount = sizeof(data[0]) / sizeof(data[0][0]);
Table table = {
.title = "This is a table",
.headers = headers,
.data = (char ***)data,
.rowCount = rowCount,
.colCount = colCount,
.sizes = NULL,
.callback = tableCallback
};
displayTable(&table);
// Guided prompt example
Option options[] = {
{"hello", "Hello world", (char *[]){"a", "b", "c"}, 3},
{"hello_again", NULL, NULL, 0}
};
displayGPrompt("This is a guided prompt", "Type something", options,
sizeof(options) / sizeof(options[0]));
return 0;
}
void initNcurses() {
initscr();
cbreak();
noecho();
keypad(stdscr, TRUE);
}
// Function to display a logger message
void displayLogger(Logger *logger) {
printw("%s\n", logger->message);
refresh();
}
// Function to display a confirmation box
void displayBox(int x, int y, int width, int height, const char *message,
void (*yesCallback)(void), void (*noCallback)(void)) {
WINDOW *box = newwin(height, width, y, x);
box(box, 0, 0);
mvwprintw(box, height / 2, (width - strlen(message)) / 2, "%s", message);
wrefresh(box);
int key;
while ((key = getch()) != 'q') {
if (key == 'y' && yesCallback != NULL) {
yesCallback();
break;
} else if (key == 'n' && noCallback != NULL) {
noCallback();
break;
}
}
delwin(box);
}
// Function to handle keypress event
void onKeyPress(char key) {
if (key == 27) { // ESC key
displayBox(10, 5, 40, 6, "Exit?", NULL, NULL); // No callbacks for simplicity }
}
int main() {
// Initialize ncurses
initNcurses();
// Logger example
Logger logger = {"This is logged onto the display"};
displayLogger(&logger);
// Add keypress listener
while (1) {
char key = getch();
onKeyPress(key);
}
// End ncurses
endwin();
return 0;
}
void initNcurses() {
initscr();
cbreak();
noecho();
keypad(stdscr, TRUE);
}
// Function to display the terminal
void displayTerminal(Terminal *terminal) {
printw("%s\n", terminal->title);
refresh();
char input[100];
while (1) {
printw("%s ", terminal->prompt);
refresh();
getstr(input);
if (strcmp(input, "exit") == 0) {
break;
}
terminal->callback(terminal->prompt, input);
}
}
// Example callback function for terminal
void terminalCallback(char *prompt, char *input) {
printw("%s%s\n", prompt, input);
refresh();
}
int main() {
// Initialize ncurses
initNcurses();
// Define and display the terminal
Terminal terminal = {
.title = "This is a terminal",
.prompt = ">",
.callback = terminalCallback
};
displayTerminal(&terminal);
// End ncurses
endwin();
return 0;
}
