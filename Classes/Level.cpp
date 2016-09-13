//
//  Level.cpp
//  Kolkakoli
//
//  Created by Liam Magee on 30/08/2016.
//
//

#include "Level.hpp"

USING_NS_CC;

Level::Level(void) {
    
}


std::vector< Cookie* > Level::createInitialCookies() {
    std::vector< Cookie* > lCookies;
    for (int i = 0; i < NumRows; i++) {
        for (int j = 0; j < NumColumns; j++) {
            if (i==0) {
                std::vector< Cookie* > col;
                cookies.push_back(col);
            }
            if (tileAtColumn(j, i) == NULL) {
                cookies[j].push_back(NULL);
                continue;
            }
            int cookieType = 0;
            do {
                cookieType = rand() % Cookie::NumCookieTypes + 1;
            }
            while ( (j >= 2 &&
                     cookies[j - 1][i] != NULL &&
                     cookies[j - 2][i] != NULL &&
                     cookies[j - 1][i]->cookieType == cookieType &&
                     cookies[j - 2][i]->cookieType == cookieType) ||
                   (i >= 2 &&
                    cookies[j][i - 1]!= NULL &&
                    cookies[j][i - 2]!= NULL &&
                    cookies[j][i - 1]->cookieType == cookieType &&
                    cookies[j][i - 2]->cookieType == cookieType));
            
            Cookie* cookie = createCookieAtColumn(j, i, cookieType);
            lCookies.push_back(cookie);
        }
    }
    
    return lCookies;
}

void Level::detectPossibleSwaps() {
    std::vector<Swap*> set;
    for (int i = 0; i < NumRows; i++) {
        for (int j = 0; j < NumColumns; j++) {
            Cookie* cookie = cookies[j][i];
            if (cookie != NULL) {
                if (j < NumColumns - 1) {
                    Cookie* other = cookies[j + 1][i];
                    if (other != NULL) {
                        
                        cookies[j][i] = other;
                        cookies[j + 1][i] = cookie;
                        
                        if (hasChainAtColumn(j, i) || hasChainAtColumn(j + 1, i)) {
                            Swap *swap = new Swap();
                            swap->cookieA = cookie;
                            swap->cookieB = other;
                            set.push_back(swap);
                        }

                        cookies[j][i] = cookie;
                        cookies[j + 1][i] = other;
                    }
                }
                if (i < NumRows - 1) {
                    Cookie* other = cookies[j][i + 1];
                    if (other != NULL) {
                        
                        cookies[j][i] = other;
                        cookies[j][i + 1] = cookie;
                        
                        if (hasChainAtColumn(j, i) || hasChainAtColumn(j, i + 1)) {
                            Swap *swap = new Swap();
                            swap->cookieA = cookie;
                            swap->cookieB = other;
                            set.push_back(swap);
                        }
                        
                        cookies[j][i] = cookie;
                        cookies[j][i + 1] = other;
                    }
                }
            }
        }
    }
    possibleSwaps = set;
}

bool Level::hasChainAtColumn(int col, int row) {
    int cookieType = cookies[col][row]->cookieType;
    
    int horzLength = 1;
    for (int i = col - 1; i >= 0 && cookies[i][row] != NULL && cookies[i][row]->cookieType == cookieType; i--, horzLength++) ;
    for (int i = col + 1; i < NumColumns && cookies[i][row] != NULL && cookies[i][row]->cookieType == cookieType; i++, horzLength++) ;
    if (horzLength >= 3)
        return true;
    
    int vertLength = 1;
    for (int i = row - 1; i >= 0 && cookies[col][i] != NULL && cookies[col][i]->cookieType == cookieType; i--, vertLength++) ;
    for (int i = row + 1; i < NumRows && cookies[col][i] != NULL && cookies[col][i]->cookieType == cookieType; i++, vertLength++) ;
    return (vertLength >= 3);
}

Cookie* Level::createCookieAtColumn(int col, int row, int cookieType) {
    Cookie* cookie = new Cookie();
    cookie->cookieType = cookieType;
    cookie->col = col;
    cookie->row = row;
    if (row >= cookies[col].size())
        cookies[col].push_back(cookie);
    else
        cookies[col][row] = cookie;
    return cookie;
}

std::vector< Cookie* > Level::shuffle() {
    
    std::vector< Cookie* > lCookies;
    do {
        lCookies = createInitialCookies();
        detectPossibleSwaps();
    }
    while (possibleSwaps.size() == 0);

    return lCookies;
}


Cookie* Level::cookieAtColumn(int col, int row) {
    if (col == -1 || row == -1)
        return NULL;
    return cookies[col][row];
}

void Level::loadJSON(const std::string& filename, Level *level) {
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename);
    unsigned long bufferSize = 0;
    Data mFileData = CCFileUtils::sharedFileUtils()->getDataFromFile(fullPath.c_str());
    //const char* mFileData = (const char*)CCFileUtils::getFileData(fullPath.c_str(), "r", &bufferSize);

    unsigned char* data;
    size_t len = mFileData.getSize();
    data = mFileData.getBytes();
    
    rapidjson::Document document;
    //document.Parse(clearData.c_str());
    document.Parse(reinterpret_cast< char const* >(data));
    //const int targetScore = document["targetScore"].GetInt();
    //const int moves = document["moves"].GetInt();
    level->targetScore = document["targetScore"].GetInt();
    level->maximumMoves = document["moves"].GetInt();
    const auto& tiles = document["tiles"];
    //rapidjson::Value& tiles = document["tiles"];
    
    int cols = 0;
    for (rapidjson::Value::ConstValueIterator itr = tiles.Begin(); itr != tiles.End(); ++itr) {
        const auto& cells = itr;
        int rows = 0;
        std::vector< ::Tile* > row;
        for (rapidjson::Value::ConstValueIterator cellItr = cells->Begin(); cellItr != cells->End(); ++cellItr) {
            ::Tile* tile = new ::Tile();
            if (cellItr->GetInt() == 1) {
                tile->on = true;
            }
            else {
                tile->on = false;
            }
            row.push_back(tile);
            rows++;
        }
        level->tiles.push_back(row);
    }
}

Level* Level::initWithFile(const std::string& filename) {
    Level *level = new Level::Level;
    loadJSON(filename, level);
    
    return level;
}


::Tile* Level::tileAtColumn(int col, int row) {
    if (col==-1||row==-1)
        return NULL;
    if (tiles[col][row]->on)
        return tiles[col][row];
    else
        return NULL;
}
void Level::performSwap(Swap* swap) {
     int columnA = swap->cookieA->col;
     int rowA = swap->cookieA->row;
     
     int columnB = swap->cookieB->col;
     int rowB = swap->cookieB->row;
     
     cookies[columnA][rowA] = swap->cookieB;
     swap->cookieB->col = columnA;
     swap->cookieB->row = rowA;
     
     cookies[columnB][rowB] = swap->cookieA;
     swap->cookieA->col = columnB;
     swap->cookieA->row = rowB;
}
bool Level::isPossibleSwap(Swap* swap) {
    auto it = std::find_if(possibleSwaps.begin(), possibleSwaps.end(), [&swap](const Swap* s) {
        return *swap == *s;
    });
    if(it != possibleSwaps.end()) {
        return true;
    } else {
        return false;
    }
}

std::vector< Chain* > Level::removeMatches() {
    std::vector< Chain* > matches;
    std::vector< Chain* > horzMatches = detectHorizontalMatches();
    std::vector< Chain* > vertMatches = detectVerticalMatches();
    calculateScores(horzMatches);
    calculateScores(vertMatches);
    removeCookies(horzMatches);
    removeCookies(vertMatches);
    //std::cout << "Horiztontal matches: " << horzMatches.size() << std::endl;
    //std::cout << "Vertical matches: " << vertMatches.size() << std::endl;
    horzMatches.insert( horzMatches.end(), vertMatches.begin(), vertMatches.end() );
    return horzMatches;
}
void Level::removeCookies(std::vector< Chain* > chains) {
    for (Chain* chain : chains) {
        for (Cookie* cookie : chain->cookies) {
            cookies[cookie->col][cookie->row] = NULL;
        }
    }
}
std::vector< Chain* > Level::detectHorizontalMatches()  {
    std::vector< Chain* > matches;
    for (int i = 0; i < NumRows; i++) {
        for (int j = 0; j < NumColumns - 2; ) {
            Cookie* cookie = cookies[j][i];
            if (cookie!=NULL) {
                int cookieType = cookie->cookieType;
                if (cookies[j+1][i] != NULL &&
                    cookies[j+1][i]->cookieType == cookieType &&
                    cookies[j+2][i] != NULL &&
                    cookies[j+2][i]->cookieType == cookieType) {
                    Chain* chain = new Chain();
                    chain->chainType = ChainTypeHorizontal;
                    chain->addCookie(cookie);
                    do {
                        chain->addCookie(cookies[j][i]);
                        j += 1;
                    }
                    while (j < NumColumns && cookies[j][i]!=NULL && cookies[j][i]->cookieType == cookieType);
                    matches.push_back(chain);
                    continue;
                }
            }
            j++;
        }
    }
    return matches;
}
std::vector< Chain* > Level::detectVerticalMatches() {
    std::vector< Chain* > matches;
    for (int j = 0; j < NumColumns; j++) {
        for (int i = 0; i < NumRows - 2; ) {
            Cookie* cookie = cookies[j][i];
            if (cookie!=NULL) {
                int cookieType = cookie->cookieType;
                if (cookies[j][i+1] != NULL &&
                    cookies[j][i+1]->cookieType == cookieType &&
                    cookies[j][i+2] != NULL &&
                    cookies[j][i+2]->cookieType == cookieType) {
                    Chain* chain = new Chain();
                    chain->chainType = ChainTypeHorizontal;
                    do {
                        chain->addCookie(cookies[j][i]);
                        i += 1;
                    }
                    while (i < NumRows && cookies[j][i]!=NULL && cookies[j][i]->cookieType == cookieType);
                    matches.push_back(chain);
                    continue;
                }
            }
            i++;
        }
    }
    return matches;
}

std::vector< std::vector< Cookie* > > Level::fillHoles() {
    std::vector< std::vector< Cookie* > > columns;
    for (int j = 0; j < NumColumns; j++) {
        std::vector< Cookie* > rows;
        for (int i = 0; i < NumRows; i++) {
            if (tiles[j][i] != NULL && tiles[j][i]->on && cookies[j][i] == NULL) {
                for (int k = i + 1; k < NumRows; k++) {
                    Cookie* cookie = cookies[j][k];
                    if (cookie != NULL) {
                        cookies[j][k] = NULL;
                        cookies[j][i] = cookie;
                        cookie->row = i;
                        rows.push_back(cookie);
                        break;
                    }
                }
            }
        }
        if (rows.size() > 0)
            columns.push_back(rows);
    }
    return columns;
}


std::vector< std::vector< Cookie* > > Level::topUpCookies() {
    std::vector< std::vector< Cookie* > > columns;
    int cookieType = 0;
    for (int j = 0; j < NumColumns; j++) {
        std::vector< Cookie* > rows;
        for (int i = NumRows - 1; i >= 0 && cookies[j][i] == NULL; i--) {
            if (tiles[j][i] != NULL && tiles[j][i]->on) {
                
                int newCookieType = 0;
                do {
                    newCookieType = rand() % Cookie::NumCookieTypes + 1;
                }
                while ( newCookieType == cookieType );
                cookieType = newCookieType;
                
                Cookie* cookie = createCookieAtColumn(j, i, cookieType);
                rows.push_back(cookie);

            }
        }
        if (rows.size() > 0)
            columns.push_back(rows);
    }
    return columns;
}

void Level::calculateScores(std::vector< Chain* > chains) {
    for (Chain* chain : chains) {
        chain->score = 60 * (chain->cookies.size() - 2);
    }
}