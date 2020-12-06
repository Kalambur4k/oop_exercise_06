#include <iostream>
#include <utility>
#include <algorithm>
#include <locale>

#include "queue.cpp"
#include "FigureT.cpp"

void printmenu() {
    std::cout << std::endl << "1 - Add Figure to Queue" << std::endl;
    std::cout << "2 - Remove Figure from Queue" << std::endl;
    std::cout << "3 - Print Figures from Queue" << std::endl;
    std::cout << "4 - Figures Square Comparison" << std::endl;
    std::cout << "5 - Print Menu" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "6 - Exit" << std::endl;
}

void Print(Queue<Rectangle<int>> &q) {
    std::for_each(q.Begin(), q.End(), [](Rectangle<int>& e){
        std::cout << e.c.first * e.c.second << std::endl;
    });
}

int main() {
	Queue<Rectangle<int>> q;
	int cmd, i, cnt;
	double sq;

    std::cout << "OOP lab #6. Author: Velesov Daniil M8O - 208B - 19." << std::endl;
    std::cout << "Hello there. It is a Rectangle Queue.\nAdd or remove Rectangles in Rectangle Queue and start comparising their square by using 4 in menu.\n " << std::endl;
    printmenu();
	while (true) {
		std::cin >> cmd;
		switch(cmd) {
            case 1: {
			    std::cout << "Add figure in top of queue or custom position" << std::endl;
			    std::cout << "Do you want push Rectangle [1] or insert it into Queue [2]?" << std::endl;
			    std::cin >> cmd;
                if(cmd == 1) {
                    Rectangle<int> rec;
				    std::cout << "Push - enter width and length: " << std::endl;
                    try {
                        std::cout << "length:" << std::endl;
					    std::cin >> rec.c.first;
					    std::cout << "width:" << std::endl;
					    std::cin >> rec.c.second;
		            } catch (std::exception &e) {
					    std::cout << e.what() << std::endl;
					    break;
				    }
					q.Push(rec);
					std::cout << "DONE!" << std::endl;
					continue;
                }
			    else if (cmd == 2) {
					Rectangle<int> rec;
					std::cout << "Insert - enter width and length:  " << std::endl;
					try {
					    std::cout << "length:" << std::endl;
						std::cin >> rec.c.first;
						std::cout << "width:" << std::endl;
					    std::cin >> rec.c.second;
					} catch (std::exception &e) {
						std::cout << e.what() << std::endl;
						break;
					}
					std::cout << "Insert - enter index to place Rectangle" << std::endl;
					std::cin >> i;
					Queue<Rectangle<int>>::ForwardIterator it = q.Begin();
					for (cnt = 0; cnt < i; cnt++) {
						it++;
					}
					q.Insert(it, rec);
					std::cout << "DONE!" << std::endl;
					continue;
				}
				else {
					std::cout << "Error: Invalid input" << std::endl;
					std::cin.clear();
					std::cin.ignore(30000, '\n');
					break;
				}
			}
			case 2: {
				std::cout << "Remove Rectangle from top of queue or custom position" << std::endl;
			    std::cout << "Pop[1] or custom remove [2]" << std::endl;
				std::cin >> cmd;
				if (cmd == 1) {
					std::cout << "DONE!" << std::endl;
					q.Pop();
					continue;
				}
				else if(cmd == 2) {
					std::cout << "Removing rectangle - enter Index ";
					std::cin >> i;
					Queue<Rectangle<int>>::ForwardIterator it = q.Begin();
					for (cnt = 0; cnt < i; cnt++) {
						it++;
					}
					q.Erase(it);
					std::cout << "DONE!" << std::endl;
					continue;
				}
				else {
					std::cout << "Error: Invalid input" << std::endl;
					std::cin.clear();
					std::cin.ignore(30000, '\n');
					break;
				}
			}
			case 3: {
				std::cout << "Print Queue" << std::endl;
				Print(q);
				std::cout << "DONE!" << std::endl;
				continue;
			}

			case 4: {
				std::cout << "Square Comparison - enter square " << std::endl;
				std::cin >> sq;
				std::cout << "The number of figures with square less than given "
					<< std::count_if(q.Begin(), q.End(), [sq](Rectangle<int> t){
					return t.c.first*t.c.second < sq;
				}) << std::endl;
				std::cout << "DONE!" << std::endl;
				continue;
			}
			case 6: {
				return 0;
			}
			case 5: {
                printmenu();
				continue;
			}
			default: {
				std::cout << "Error: Invalid input" << std::endl;
				std::cin.clear();
				std::cin.ignore(30000, '\n');
			}
		}
	}
	return 0;
}
