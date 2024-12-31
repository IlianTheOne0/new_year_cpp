#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include <random>
#include <chrono>
#include <ctime>

using std::cout;
using std::endl;
using std::cin;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::chrono::system_clock;
using std::time_t;
using std::localtime;
using std::put_time;

HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
int y_coord = (24 - 4) / 2;
int x_coord = 124 / 2;

int main();

void gotoxy(int x, int y) {
    COORD pos = { x, y };

    SetConsoleCursorPosition(output, pos);

    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = 124;
    windowSize.Bottom = 24;

    SetConsoleWindowInfo(output, TRUE, &windowSize);
}

void setcolor(unsigned short color) {
	SetConsoleTextAttribute(output, color);
}

void set_background_color(unsigned short color) {
	SetConsoleTextAttribute(output, (color << 4) | 0x0F);
}

int length_counter(const char* text)
{
    unsigned long long j{};
    int line_length{};

    while (text[j] != '\0')
    {
        line_length++;
        j++;
    }

    return line_length;
}

void countdown() {
    auto now = system_clock::now();
    time_t now_time = system_clock::to_time_t(now);

    tm local_time;
    localtime_s(&local_time, &now_time);

    int year = local_time.tm_year + 1900 + 1;
    tm next_year_time{};
    next_year_time.tm_year = year - 1900;
    next_year_time.tm_mon = 0;
    next_year_time.tm_mday = 1;
    next_year_time.tm_hour = 0;
    next_year_time.tm_min = 0;
    next_year_time.tm_sec = 0;

    int days_in_year = 365;
    if ((local_time.tm_year % 4 == 0 && local_time.tm_year % 100 != 0) || (local_time.tm_year % 400 == 0)) {
        days_in_year = 366;
    }

    int days_diff = (next_year_time.tm_yday - local_time.tm_yday) + (days_in_year * (next_year_time.tm_year - local_time.tm_year));
    int hours_diff = next_year_time.tm_hour - local_time.tm_hour;
    int minutes_diff = next_year_time.tm_min - local_time.tm_min;
    int seconds_diff = next_year_time.tm_sec - local_time.tm_sec;

    if (seconds_diff < 0) {
        seconds_diff += 60;
        minutes_diff -= 1;
    }
    if (minutes_diff < 0) {
        minutes_diff += 60;
        hours_diff -= 1;
    }
    if (hours_diff < 0) {
        hours_diff += 24;
        days_diff -= 1;
    }

    int total_seconds_diff = (days_diff * 24 * 3600) + (hours_diff * 3600) + (minutes_diff * 60) + seconds_diff;

    int days = total_seconds_diff / (24 * 3600);
    total_seconds_diff -= days * 24 * 3600;
    int hours = total_seconds_diff / 3600;
    total_seconds_diff -= hours * 3600;
    int minutes = total_seconds_diff / 60;
    int seconds = total_seconds_diff % 60;

    gotoxy(32, 15);
    cout << "Countdown to " << year << ": "
        << days << " days, "
        << hours << " hours, "
        << minutes << " minutes, "
        << seconds << " seconds" << endl;
}

void incorrect(const char* message)
{
    SetConsoleTextAttribute(output, 4);
    cout << "Incorrect " << message << endl;
    SetConsoleTextAttribute(output, 7);
}

void correct()
{
    SetConsoleTextAttribute(output, 2);
    cout << "Correct!\t\t\t" << endl;
    SetConsoleTextAttribute(output, 7);
}

void menu(int selected) {
    system("cls");
    y_coord = (24 - 4) / 2;

    for (int i = 1; i <= 3; i++)
    {
        if (i == selected) {
            set_background_color(0x0A);
        }
        else {
            setcolor(7);
        }

        const char* message = nullptr;

        switch (i) {
            case 1: {
                message = "Wishes for the New Year";
                gotoxy(x_coord - (length_counter(message) / 2), y_coord);
                cout << message;
            } break;

            case 2: {
                message = "New Year's quiz";
                gotoxy(x_coord - (length_counter(message) / 2), y_coord);
                cout << message << endl;
            } break;

            case 3: {
                message = "Exit";
                gotoxy(x_coord - (length_counter(message) / 2), y_coord);
                cout << message;
            } break;
        }

        y_coord++;
    }

    SetConsoleTextAttribute(output, 7);
    countdown();

    setcolor(7);
}

void print_wrapped_text(int max_width = 47) {
    const char* beginning[] =
    {
        "Let this New Year bring",
        "We wish you a happy New Year",
        "Let it be in your life",
        "We wish you a Happy New Year",
        "Let it come true on New Year's Eve",
        "Happy New Year! We wish you",
        "Let them come with a New Year's mood",
        "We wish the New Year to bring you everything you need",
        "Let the fairy-tale spirit of the holiday bring",
        "Let the Christmas tree shine with lights and bring good luck",
        "Winter magic is a gift",
        "We wish you a happy New Year",
        "Let it be in your home",
        "Let all dreams come true",
        "Let it come with new opportunities",
        "Let the snowflakes come",
        "May the New Year always have room for",
        "Happy New Year, let it be",
        "We wish it to appear in 2025",
        "Let it always live in your heart"
    };
    const char* middle[] =
    {
        "happiness, health and prosperity,",
        "peace, harmony and love,",
        "success in all matters,",
        "creative ideas and new discoveries,",
        "family comfort and warm hugs,",
        "joy, sincere smiles,",
        "happy moments with friends,",
        "new achievements and accomplishments,",
        "unexpected joys,",
        "support of family and friends,",
        "harmony in the soul,",
        "well-being and joy,",
        "inspiration and strength,",
        "pleasant surprises,",
        "faith in the best,",
        "warmth and kindness,",
        "cheerful holidays,",
        "new acquaintances and adventures,",
        "fabulous events,",
        "unforgettable moments,"
    };
    const char* end[] =
    {
        "and a lot of bright moments!",
        "and the fulfillment of all dreams!",
        "and unforgettable travels!",
        "and good friends by your side!",
        "and incredible adventures!",
        "and new achievements!",
        "and unquenchable optimism!",
        "and many pleasant memories!",
        "and wonderful holidays!",
        "and lots and lots of happiness!",
        "and warm family evenings!",
        "and bright emotions!",
        "and wonderful gifts!",
        "and new impressions!",
        "and joyful moments!",
        "and inexhaustible energy!",
        "and a sea of positive!",
        "and love in every day!",
        "and a bright hope for the future!",
        "and a real winter fairy tale!"
    };

    unsigned long long general_i{};
    bool in_word{ false };

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 19);

    const char* beginning_message = beginning[dist(gen)];
    const char* middle_message = middle[dist(gen)];
    const char* end_message = end[dist(gen)];

    gotoxy(2, 11);

    char message[256];
    int index = 0;

    for (int i = 0; beginning_message[i] != '\0'; ++i, index++) {
        message[index] = beginning_message[i];
    }
    message[index++] = ' ';

    for (int i = 0; middle_message[i] != '\0'; i++, index++) {
        message[index] = middle_message[i];
    }
    message[index++] = ' ';

    for (int i = 0; end_message[i] != '\0'; i++, index++) {
        message[index] = end_message[i];
    }
    message[index] = '\0';

    unsigned long long i = 0;
    int line_length = length_counter(message);
    int console_width = 124;
    int start_position = (console_width - line_length) / 2;

    for (int i = 0; i < start_position; i++)
    {
        cout << ' ';
    }
    while (message[i] != '\0')
    {
        cout << message[i];
        i++;
    }

    cout << " ";
    general_i++;

    cout << endl;
}

void quiz()
{
    const char* questions[] = {
        "What is the traditional New Year's Eve celebration in Times Square?",
        "Which country celebrates New Year's with a large feast of 12 grapes at midnight?",
        "What is the most common New Year's resolution?",
        "Which animal is associated with the Chinese New Year for 2024?",
        "What year did the United Nations designate as the International Year of Peace and Trust?",
        "Which ancient civilization is credited with creating the first recorded New Year's celebration?",
        "What is the New Year's Eve tradition in Japan where people listen to 108 bells?",
        "In which country do people celebrate New Year's by throwing old furniture out of windows?",
        "What drink is most often associated with toasts on New Year's Eve?",
        "Which city is known for having one of the largest New Year's Eve fireworks displays in the world?",
        "What color is often worn on New Year's Eve in Brazil for good luck?",
        "What time does the New Year's countdown usually begin in New York's Times Square?",
        "Which of these is NOT a typical New Year's tradition in the United States?",
        "What is the New Year's celebration called in Scotland?",
        "Which of these foods is considered a symbol of good luck in the Southern United States on New Year's Day?",
        "Which country celebrates the New Year by wearing giant, colorful costumes for street parades?",
        "In the UK, what is the tradition of 'first-footing'?",
        "Which country celebrates New Year's with a ritual of burning effigies representing the old year?",
        "Which popular New Year's song is traditionally sung at the stroke of midnight?"
    };
    const char* options[][4] = {
        {"A) Fireworks", "B) Ball drop", "C) Parade", "D) Concert"},
        {"A) Italy", "B) Spain", "C) Mexico", "D) Greece"},
        {"A) Travel more", "B) Exercise more", "C) Learn a new language", "D) Save more money"},
        {"A) Rabbit", "B) Dragon", "C) Tiger", "D) Snake"},
        {"A) 2000", "B) 2020", "C) 2017", "D) 2024"},
        {"A) Romans", "B) Egyptians", "C) Babylonians", "D) Greeks"},
        {"A) Setsubun", "B) Bonenkai", "C) Joya no Kane", "D) Shinto Blessing"},
        {"A) Argentina", "B) Italy", "C) South Africa", "D) Brazil"},
        {"A) Wine", "B) Beer", "C) Champagne", "D) Whiskey"},
        {"A) New York", "B) Dubai", "C) Sydney", "D) London"},
        {"A) Red", "B) White", "C) Green", "D) Blue"},
        {"A) 10:00 PM", "B) 11:00 PM", "C) 11:59 PM", "D) Midnight"},
        {"A) Eating black-eyed peas", "B) Watching the Rose Parade", "C) Kissing at midnight", "D) Jumping into a river"},
        {"A) Hogmanay", "B) Tartan Night", "C) Burns Supper", "D) Caledonia Day"},
        {"A) Mashed potatoes", "B) Black-eyed peas", "C) Tacos", "D) Pancakes"},
        {"A) Colombia", "B) Brazil", "C) Spain", "D) South Africa"},
        {"A) The first person to sing a song at midnight", "B) The first person to enter the house after midnight", "C) The first person to walk through your door on New Year's Day", "D) The first person to arrive at your house brings gifts"},
        {"A) Japan", "B) Mexico", "C) Ecuador", "D) Peru"},
        {"A) Auld Lang Syne", "B) Happy New Year", "C) Jingle Bells", "D) Let It Snow"}
    };
    const int correct_answers[] = {
        1, // B) Ball drop
        1, // B) Spain
        1, // B) Exercise more
        0, // A) Rabbit
        3, // D) 2024
        2, // C) Babylonians
        2, // C) Joya no Kane
        2, // C) South Africa
        2, // C) Champagne
        2, // C) Sydney
        1, // B) White
        1, // B) 11:00 PM
        3, // D) Jumping into a river
        0, // A) Hogmanay
        1, // B) Black-eyed peas
        1, // B) Brazil
        1, // B) The first person to enter the house after midnight
        2, // C) Ecuador
        0  // A) Auld Lang Syne
    };

    char input;
    int user_answer;
    int console_width = 124;
    int line_length;
    int start_position;
    int correct_answers_counter{};

    for (int i = 0; i < 19; i++)
    {
        system("cls");

        gotoxy(x_coord - (15 / 2), 5);
        cout << "New Year's quiz";

        gotoxy(2, 11);

        line_length = length_counter(questions[i]) + ((i < 10) ? 14 : 15);
        start_position = (console_width - line_length) / 2;
        gotoxy(start_position, 10);
        line_length = {}, start_position = {};

        cout << "Question " << i + 1 << ": " << questions[i] << endl << endl;

        for (int j = 0; j < 4; j++)
        {
            line_length = length_counter(options[i][j]);
            start_position = (console_width - line_length) / 2;
            gotoxy(start_position, j + 12);

            cout << options[i][j] << endl;
        }
        line_length = {}, start_position = {};

        do
        {
            line_length = 28;
            start_position = (console_width - line_length) / 2;
            gotoxy(start_position, 19);

            cout << "Enter the option (letter): ";
            cin >> input;

            if (input < 'A' || input > 'D')
            {
                incorrect("option");
                continue;
            }
            break;
        } while (true);
        user_answer = int(input) - 65;

        if (user_answer == correct_answers[i])
        {
            gotoxy(start_position, 20);
            correct();
            correct_answers_counter++;
        }
        else
        {
            gotoxy(start_position, 20);
            incorrect("answer");
            gotoxy(start_position, 21);
            cout << "Correct answer is " << char(correct_answers[i] + 65) << endl;
        }

        gotoxy(0, 24 - 1);
        system("pause");
    }

    system("cls");

    line_length = 28;
    start_position = (console_width - ((correct_answers_counter < 10) ? 4 : 5)) / 2;
    gotoxy(start_position, 5);
    cout << correct_answers_counter << "/19" << endl;

    line_length = 28;
    start_position = (console_width - ((correct_answers_counter < 10) ? 4 : 5)) / 2;
    gotoxy(start_position, 6);
    cout << ((correct_answers_counter < 10) ? "BAD!" : "GOOD!") << endl;

    gotoxy(0, 24 - 1);
    system("pause");
    main();
}

int main()
{
    int selected{ 1 };
    menu(selected);

    while (true) {
        char choice = _getch();

        if (choice == -32) {
            choice = _getch();

            switch (choice) {
                case 72: { if (selected > 1) selected--; } break;
                case 80: { if (selected < 3) selected++; } break;
            }

            menu(selected);
        }
        else if (choice == 13) {
            system("cls");

            switch (selected) {
                case 1:
                {
                    gotoxy(x_coord - (23 / 2), 5);
                    cout << "Wishes for the New Year";

                    print_wrapped_text();
                } break;

                case 2:
                {
                    quiz();
                }

                case 3:
                {
                    return 0;
                } break;
            }

            gotoxy(0, 24 - 1);
            system("pause");
            menu(selected);
        }
    }

	//char ch = _getch();
	return 0;
}