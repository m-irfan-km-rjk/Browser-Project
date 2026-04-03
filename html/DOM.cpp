#include "DOM.hpp"
#include <unordered_map>
#include <string>

Document::Document() {

}

void Document::appendChild(DOMNode& node) {
	root->children.push_back(&node);
}