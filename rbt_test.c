#include "rbt.h"

void simpleTest()
{
	// Int Tree Tests	
	RedBlackTree<int, char> rb1;
	if (rb1.insert(6, 'f')) cout << "inserted 42" << endl;
	rb1.insert(10, 'j');
	rb1.insert(2, 'b');
	RedBlackTree<int, char> rb2(rb1);
 
	if (rb1.remove(2)) cout << "removed 2" << endl;
	if (rb1.search(6)) cout << "found 6" << endl;
 
	vector<char> v1 = rb1.search(11, 21); //should contain j
	vector<char> v2 = rb1.values(); //should contain {f, j}
	vector<int> v3 = rb1.keys(); //should contain {6, 10}

	for(int i = 0; i < v1.size(); i++)
		cout << v1[i] << ", ";
	cout << endl << endl;

	for(int i = 0; i < v2.size(); i++)
		cout << v2[i] << ", ";
	cout << endl << endl;

	for(int i = 0; i < v3.size(); i++)
		cout << v3[i] << ", ";
	cout << endl << endl;
 
	cout << "size = " << rb1.size() << endl; //should be 2
	NodeT<int, char>* pRoot = rb1.getRoot(); //BAD design - for our testing only
}

/*//for testing
	void preOrderPrint(NodeT<T1, T2>* node) const
	{
		if(node != nullptr)
		{
			cout << node->key << ", " << node->value << ", " << node->isBlack << endl;
			preOrderPrint(node->left);
			preOrderPrint(node->right);
		}
	}

		void print() const
	{
		preOrderPrint(root);
	}*/

int main()
{
	simpleTest();

	/*RedBlackTree<float, float> rbt;
	rbt.insert(70, 1);
	rbt.insert(80, 2);
	rbt.print();
	rbt.remove(70);
	cout << "after removal" << endl;
	rbt.print();
	cout << rbt.getRoot()->key << endl;*/

	/*rbt.insert(1, 1);
	rbt.insert(2, 1);
	rbt.insert(3, 1);
	rbt.insert(4, 1);
	rbt.insert(5, 1);
	rbt.insert(6, 1);
	rbt.insert(7, 1);
	rbt.insert(8, 1);
	rbt.insert(9, 1);
	rbt.insert(10, 1);

	rbt.print();
	cout << endl << endl;
	cout << rbt.getRoot()->key << endl;*/

	/*RedBlackTree<int, int> rbt;
	rbt.insert(50, 1);
	rbt.insert(25, 2);
	rbt.insert(10, 4);
	rbt.insert(5, 6);
	rbt.insert(15, 7);
	rbt.insert(35, 5);
	rbt.insert(75, 3);
	rbt.insert(60, 8);
	rbt.insert(55, 9);
	rbt.insert(70, 10);
	rbt.insert(65, 11);
	rbt.insert(72, 12);
	rbt.insert(85, 13);
	rbt.insert(80, 14);
	rbt.insert(78, 15);
	rbt.insert(82, 16);
	rbt.insert(100, 17);
	rbt.insert(90, 18);
	rbt.insert(88, 19);
	rbt.insert(92, 20);
	rbt.insert(110, 21);
	rbt.insert(120, 22);
	rbt.insert(80, 23);

	cout << "printing" << endl << endl;
	rbt.print();

	cout << endl << rbt.getRoot()->key << endl;
	cout << rbt.size() << endl;

	rbt.remove(70);//(120);//(82);//(85);

	cout << endl << endl;
	cout << "printing" << endl << endl;
	rbt.print();

	cout << endl << rbt.getRoot()->key << endl;
	cout << rbt.size() << endl;

	/*rbt.remove(120);//(82);//(85);

	cout << endl << endl;
	cout << "printing" << endl << endl;
	rbt.print();

	cout << endl << rbt.getRoot()->key << endl;
	cout << rbt.size() << endl;

	RedBlackTree<int, int> rbt2 = rbt;
	cout << endl << endl;
	rbt2.print();
	cout << endl << rbt.getRoot()->key << endl;
	cout << rbt.size() << endl;
	cout << endl << endl;

	rbt2 = rbt2;
	cout << endl << endl;
	rbt2.print();
	cout << endl << rbt.getRoot()->key << endl;
	cout << rbt.size() << endl;
	cout << endl << endl;

	RedBlackTree<int, int> rbt3;
	rbt3 = rbt2;
	cout << endl << endl;
	rbt3.print();
	cout << endl << rbt.getRoot()->key << endl;
	cout << rbt.size() << endl;
	cout << endl << endl;

	RedBlackTree<int, int> rbt4;
	rbt3.~RedBlackTree();
	rbt4 = rbt3;
	cout << endl << endl;
	rbt3.print();
	cout << endl << rbt.getRoot()->key << endl;
	cout << rbt.size() << endl;
	cout << endl << endl;

	cout << endl << endl;
	rbt4.print();
	cout << endl << rbt.getRoot()->key << endl;
	cout << rbt.size() << endl;
	cout << endl << endl;

	if(rbt.search(50) == true)
		cout << "Key found in rbt" << endl;
	else
		cout << "Key not found in rbt" << endl;
	cout << endl << endl;

	if(rbt.search(130) == true)
		cout << "Key found in rbt" << endl;
	else
		cout << "Key not found in rbt" << endl;
	cout << endl << endl;

	vector<int> A = rbt.search(5, 65);
	for(int i = 0; i < A.size(); i++)
		cout << A[i] << ",  ";
	cout << endl << endl;

	vector<int> D = rbt.search(1, 130);
	for(int i = 0; i < D.size(); i++)
		cout << D[i] << ",  ";
	cout << endl << endl;

	vector<int> E = rbt.search(5, 130);
	for(int i = 0; i < E.size(); i++)
		cout << E[i] << ",  ";
	cout << endl << endl;

	vector<int> F = rbt.search(1, 65);
	for(int i = 0; i < F.size(); i++)
		cout << F[i] << ",  ";
	cout << endl << endl;

	vector<int> B = rbt.values();
	for(int i = 0; i < B.size(); i++)
		cout << B[i] << ",  ";
	cout << endl << endl;

	vector<int> C = rbt.keys();
	for(int i = 0; i < C.size(); i++)
		cout << C[i] << ",  ";
	cout << endl << endl;*/


	system("pause");
	return 0;
}