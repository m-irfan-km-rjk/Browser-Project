#pragma once

#include <unordered_map>
#include <string>

struct DOMNode {
	DOMNode* parent;
	std::string tag;
	std::string text;
	std::unordered_map<std::string, std::string> attribs;
	std::vector<DOMNode*> children;
	std::vector<std::string> classList;

	DOMNode(std::string tag, DOMNode* p = nullptr) : tag(tag), parent(p) {}
};

class Document {
private:

public:
	DOMNode* root = nullptr;
	std::unordered_map<std::string, DOMNode> idMap;

	Document();

	void appendChild(DOMNode &node);

};