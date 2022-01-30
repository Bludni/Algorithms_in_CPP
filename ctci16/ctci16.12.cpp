#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <unordered_map>

//xml encoder
class Element;
std::string& ltrim(std::string&);
std::string& rtrim(std::string&);
void parseEl(std::ifstream&, Element&);
void parseChildren(std::ifstream&, Element&);

class Element {
    public:
        struct Attr {
            std::string tag;
            std::string value;
        };
        std::string tag; // present on all except textual elements
        std::string value; // present only if elem is textual
        std::vector<Attr> attrs;
        std::vector<Element> children;
        Element(std::string t = "", std::string v = ""): tag(t), value(v) {}

        void xmlEncoder(std::unordered_map<std::string, int> tag_codes)
        {
            if (this->tag == "document") { //document is a shadow tag so we just use its children
                for (auto child : children)
                    child.xmlEncoder(tag_codes);
                return;
            }
            if (this->tag == "") { //if it is a pure text child
                std::cout << this->value << " ";
                return;
            }
            
            std::cout << tag_codes[this->tag] << " "; //tag code
            for (auto attr : attrs)
                std::cout << tag_codes[attr.tag] << " " << attr.value << " ";
            std::cout << "0 "; //end of first tag
            for (auto child : children)
                child.xmlEncoder(tag_codes); 
            std::cout << "0 "; //ending tag
        }
};


void parseAttr(std::string &attr, Element &el)
{
    if (attr.empty()) return;
    Element::Attr attrib;
    size_t ws_pos = attr.find_first_of(" =");
    attrib.tag = attr.substr(0, ws_pos);
    attr.erase(0, ws_pos); // parse attrib name and erase to first ws
    
    ws_pos = attr.find_first_not_of(" =\"");
    attr.erase(0, ws_pos); //find begining of value and erase till it

    ws_pos = attr.find_first_of(" \"");
    attrib.value = attr.substr(0, ws_pos);
    attr.erase(0, ws_pos); // put value and erase till " or ws
    if (attr[ws_pos] == ' ') 
        attr.erase(0, attr.find_first_of('\"') + 1);
    else attr.erase(0, 1); // delete just "
    el.attrs.push_back(attrib);
}

void parseTag(std::string &tag, Element &el)
{
    ltrim(tag);
    size_t ws_pos = tag.find_first_of(' ');
    el.tag = tag.substr(0, ws_pos);
    tag.erase(0, ws_pos); ltrim(tag); // get the tag name
    while (!tag.empty()) { // get the attributes
        parseAttr(tag, el);
        ltrim(tag);
    }
    
}

void parseTextEl(std::ifstream &input, Element &el)
{
    std::getline(input, el.value,'<');
    rtrim(el.value);
    if (!input.eof()) input.unget(); // return '>' into stream for the continuation of parseChildren
}


void parseChildren(std::ifstream &input, Element &el)
{
    while (!input.eof()) {
        input >> std::ws;
        if (input.peek() == '<') { //if it is a regular child tag
            input.ignore(1);
            input >> std::ws;
            if (input.peek() == '/') { // if it is an ending tag
                input.ignore(1);
                std::string tag_end;
                std::getline(input,tag_end,'>');
                rtrim(tag_end);
                if (tag_end != el.tag)
                    std::cout << "Warning: wrong name of the ending tag." <<
                    "Did you think maybe " << el.tag << "?" << std::endl;
                return;
            }
            Element child;
            parseEl(input, child);
            el.children.push_back(child);
        }
        else if (!input.eof()) { //if it is a textual child
            Element child;
            parseTextEl(input, child);
            el.children.push_back(child);
        }
    }
}

void parseEl(std::ifstream &input, Element &el)
{
    std::string tag;
    std::getline(input, tag, '>');
    parseTag(tag, el);
    parseChildren(input, el);
}


Element xmlParser(std::ifstream &input)
{
    Element document("document");
    //input.ignore(std::numeric_limits<std::streamsize>::max(), '<');
    input >> std::ws;
    while (!input.eof()) {
        Element el;
        if (input.peek() == '<') {
            input.ignore(1);
            parseEl(input, el);
        }
        else parseTextEl(input, el);
        document.children.push_back(el);
        input >> std::ws;
    }
    return document;
}

std::string& ltrim(std::string &str)
{
    return str.erase(0, str.find_first_not_of(" \n\t"));
}

std::string& rtrim(std::string &str)
{
    return str.erase(str.find_last_not_of(" \n\t") + 1);
}

int main(int argc, char **argv)
{
    std::ifstream input(argv[1]);
    if (!input) {
        std::cout << "Error opening the file!" << std::endl;
        return EXIT_FAILURE;
    }
    std::unordered_map<std::string, int> tag_codes = 
    {{"family", 1}, {"person", 2}, {"firstName", 3},
    {"lastName", 4}, {"state", 5}};

    Element document = xmlParser(input);
    document.xmlEncoder(tag_codes); 
    std::cout << std::endl;
}