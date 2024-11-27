#include "SortingWrapper.hpp"

void SortingWrapper::getInput(void)
{
    std::string buf;

    std::cout << "Enter size of the array to sort (default 2500): ";
    std::getline(std::cin, buf);
    if (buf != "") size = stoi(buf);

    std::cout << "\nEnter the sorting algorithm to use.\nEnter 1 for insertion sort, 2 for mergesort, and 3 for quicksort (default 3): ";
    std::getline(std::cin, buf);
    if (buf != "") alg = static_cast<SortingWrapper::algorithm>(stoi(buf) - 1);

    std::cout << "\nEnter the maximum FPS (enter -1 for unlimited, default -1): ";
    std::getline(std::cin, buf);
    if (buf != "") fps = stoi(buf);

    /* This code is left commented, as it has no real benefit other than making it look more continuous / smooth

    std::cout << "\nEnter the maximum value in the array (default 50000): ";
    std::getline(std::cin, buf);
    if (buf != "") max_val = stoi(buf); 
    */
}

void SortingWrapper::runAlg(void)
{
    // Window setup
    sf::Vector2u dims((uint)(sf::VideoMode::getDesktopMode().width * 0.8), (uint)(sf::VideoMode::getDesktopMode().height * 0.8));
    sf::ContextSettings settings(0, 0, 8); // antialiasing level 8, all the rest are defaults
    auto window = sf::RenderWindow({ dims.x, dims.y }, "Sorting Visualizer", sf::Style::Titlebar | sf::Style::Close, settings);
    sf::Vector2u border((uint)(dims.x * 0.02), (uint)(dims.y * 0.02));

    // Generate random numbers and keep track of max value:
    int max = -1;
    for (int i = 0; i < size; i++)
    {
        list[i] = rand() % max_val + 1;
        if (list[i] > max) max = list[i];
    }

    // Rectangle setup:
    for (int i = 0; i < size; i++)
    {
        float height = ((float)list[i] / max) * (dims.y - (2 * border.y));
        float width = (float)(dims.x - (2 * border.x)) / size;
        rectList.insert(std::pair<int, sf::RectangleShape*>(list[i], new sf::RectangleShape(sf::Vector2f(width, height))));
        rectList[list[i]]->setPosition(sf::Vector2f(border.x + width * i, dims.y - height - border.y));
        rectList[list[i]]->setFillColor(sf::Color(255 - (255 * (float)list[i] / max), 255 - (255 * (float)list[i] / max), 255 - (255 * (float)list[i] / max)));
    }

    if (fps != -1) window.setFramerateLimit(fps);

    InsertionSorter iSorter(list);
    MergeSorter mSorter(list);
    QuickSorter qSorter(list);

    bool sorted = false;

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        switch (alg)
        {
        case 1:
            if (!sorted) sorted = iSorter.sort();
            break;
        case 2:
            if (!sorted) sorted = mSorter.sort();
            break;
        case 3:
            if (!sorted) sorted = qSorter.sort();
            break;
        }

        window.clear(sf::Color::White);
        for (int i = 0; i < list.size(); i++)
        {
            // Update xpos based on new position in list, and keep ypos the same
            rectList[list[i]]->setPosition(border.x + rectList[list[i]]->getSize().x * i, rectList[list[i]]->getPosition().y);
            window.draw(*rectList[list[i]]);
        }
        window.display();
    }
}