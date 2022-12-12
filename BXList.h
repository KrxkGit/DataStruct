#pragma once

template<typename TYPE>class BXList {
public:
	BXList() { 
		m_head = m_current = m_tail = NULL;
		m_count = 0; 
	}
	~BXList() {}
protected:
	struct Node
	{
		TYPE* content;
		Node* next;
		Node* fore;
	};
private:
	Node* m_head;
	Node* m_tail;
	Node* m_current;
	int m_count;
public:
	void AddTail(TYPE* node) {
		m_count += 1;
		m_current = new Node;
		if (m_head == NULL) {
			m_head = m_current;
		}
		m_current->content = node;
		m_current->fore = m_tail;
		if (m_tail != NULL) {
			m_tail->next = m_current;
		}
		m_current->next = NULL;
		m_tail = m_current;
	}
	void AddHead(TYPE* node) {
		m_count += 1;
		m_current = new Node;
		if (m_tail == NULL) {
			m_tail = m_current;
		}
		m_current->content = node;
		m_current->fore = NULL;
		m_current->next = m_head;
		if (m_head != NULL) {
			m_head->fore = m_current;
		}
		m_head = m_current;
	}
	void Insert(TYPE*node, int pos) {
		m_count += 1;

	}
	void Remove(TYPE* node) {
		for (m_current = m_head; m_current; m_current = m_current->next) {
			if (m_current->content == node) {
				if (m_current->fore != NULL) {
					m_current->fore->next = m_current->next;
				}
				if (m_current->next != NULL) {
					m_current->next->fore = m_current->fore;
				}
				if (m_current == m_head) {
					m_head = m_current->next;
				}
				if (m_current == m_tail) {
					m_tail = m_current->fore;
				}
				delete m_current;
				m_count -= 1;
				break;
			}
		}
	}
	void RemoveAll() {
		m_current = m_head;
		for (Node*temp = m_current; temp;) {
			m_current = m_current->next;
			delete temp;
			temp = m_current;
		}
		m_current = m_head = m_tail = NULL;
	}
	TYPE* GetFore() {
		m_current = m_current->fore;
		if (m_current == NULL) {
			return NULL;
		}
		return m_current->content;
	}
	TYPE* GetNext() {
		m_current = m_current->next;
		if (m_current == NULL) {
			return NULL;
		}
		return m_current->content;
	}
	TYPE* GetHead() {
		m_current = m_head;
		if (m_current == NULL) {
			return NULL;
		}
		return m_head->content;;
	}
	TYPE* GetTail() {
		m_current = m_tail;
		if (m_current == NULL) {
			return NULL;
		}
		return m_tail->content;
	}
};