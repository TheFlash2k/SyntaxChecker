#include "Stack.h"

/*
	METHOD IMPLEMENTATION FOR CLASS NODE
*/
// Constructors
Node::Node() :data(""), next(NULL) {}
Node::Node(std::string data) : data(data), next(NULL) {}
// Setters / Mutators
void Node::setData(std::string data) {
	this->data = data;
}
void Node::setNext(Node* next) {
	this->next = next;
}
// Getters / Accessors
std::string Node::getData()const {
	return this->data;
}
Node* Node::getNext()const {
	return this->next;
}
/*
	METHOD IMPLEMENTATION FOR CLASS STACK
*/
// Constructor
Stack::Stack() :root(NULL) {}
// Setter
void Stack::setTop(Node* root) {
	this->root = root;
}
// Getter
Node* Stack::getTop() {
	return root;
}
// Other Implementation method(s)
bool Stack::isEmpty() {
	return root == NULL;
}
void Stack::push(std::string data) {
	Node* temp = new Node(data); // Dynamically allocates a new Node pointer and assigns data using the default constructor
	if (isEmpty())
		temp->next = NULL;
	else
		temp->next = root;
	root = temp;
	if (DEBUG) // This function will only be invoked when debugging is enabled
		std::cout << root->data << " - pushed onto the stack!\n";
}
void Stack::push(char data) {
	std::string temp;
	temp += data; // Appends the single character to a string and pushes that string onto the stack.
	push(temp);
}
std::string Stack::pop() {
	if (isEmpty())
		return "";
	if (DEBUG) // This function will only be invoked when debugging is enabled
		std::cout << root->data << " - popped off the stack!\n";
	Node* temp = root;
	std::string _ret = root->data;
	root = root->next;
	delete temp;
	return _ret;
}
std::string Stack::top() {
	if (isEmpty())
		return "";
	return root->data;
}
// This function will only be accessible and could be invoked when debugging is enabled
void Stack::print() {
	Node* temp = root;
	while (temp != NULL) {
		std::cout << temp->data << std::endl;
		temp = temp->next;
	}
	delete temp;
}
// Destructor
Stack::~Stack() {
	delete root;
}