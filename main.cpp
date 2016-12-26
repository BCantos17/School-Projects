//
//  main.cpp
//  MPGAAstar
//
//  Created by Victor Cabrera on 8/18/15.
//  Copyright (c) 2015 Victor Cabrera. All rights reserved.
//

#include <iostream>
#include "MPGAAstar.h"
#include <ctime>
const int DEFAULT_BUFFER_SIZE = 30;
int main(int argc, const char * argv[]) {
    std::clock_t timer;
    Map * dynamicMap;
    dynamicMap = new Map(500, 400, DEFAULT_BUFFER_SIZE);
    Graph * myGraph;
    //dynamicMap->addVirtualWall("vwall1", 20, 0, 20, 60);
    //dynamicMap->addWall("wall1", 20, 0, 20, 60);
    //dynamicMap->addWall("wall2", 0, 50, 200, 0);
    //dynamicMap->addWall("wall3", 110, 90, 110, 200);
    //dynamicMap->addWall("wall4", 0, 400, 500, 400);
    myGraph = new Graph(dynamicMap, 30);
    //Adds the walls after, so it learns initial costs from an "unknown" map
    myGraph->getMap()->addVirtualWall("vwall1", 20, 0, 20, 60);
    myGraph->getMap()->addVirtualWall("vwall2", 0, 50, 200, 0);
    //myGraph->getMap()->addWall("wall1", 20, 0, 20, 60);
    //myGraph->getMap()->addWall("wall2", 0, 50, 200, 0);
    //myGraph->getMap()->addWall("wall3", 110, 90, 110, 200);
    //myGraph->getMap()->addWall("wall4", 0, 400, 500, 400);
    //myGraph->printGraph();
    //exit(1);
    Node start = myGraph->getNode(0);
    Node goal = myGraph->getNode(97);
    timer = std::clock();
    MPGAAstar tester(*myGraph,start,goal);
    double duration = ( std::clock() - timer ) / (double) CLOCKS_PER_SEC;
    cout << "time: " << duration << endl;
    return 0;
}
