# Treeset-in-java-using-C-Red-Black-Trees-

# Red-Black Tree (RBT):
1)A self-balancing binary search tree.

2)Each node of the tree is colored either red or black.

3)Maintains balance by enforcing certain rules on coloring and structure.

4)Ensures the tree remains approximately balanced, allowing for efficient search, insertion, and deletion.

# Properties:
1)Every node is either red or black.

2)The root is always black.

3)No two adjacent red nodes are allowed (red node cannot have a red parent or child).

4)Every path from a node to its descendant NULL nodes (leaves) must have the same number of black nodes.
 
# Structures:
1)struct header: Represents the header/root of the tree.

2)struct item: Represents each node of the tree, containing key, left, right, parent pointers, and a color indicator.

# Operations:
1)BST Insertion (BST_insert): Inserts a node into the binary search tree preserving the BST property.

2)RBT Insertion (Insert): Inserts a node into the RBT and then fixes any potential violations of RBT properties using rotation and recoloring (RB_Insert_Fixup).

3)BST Deletion (BST_delete): Deletes a node from the binary search tree.

4)RBT Deletion (Erase): Deletes a node from the RBT and then fixes any potential violations of RBT properties using rotation and recoloring (RB_Delete_Fixup).

5)Rotation (leftrotate, rightrotate): Performs left or right rotation around a given node, maintaining the binary search tree property.

6)Transplant (transplant): Replaces one subtree as a child of its parent with another subtree.

7)Search (Find): Searches for a key in the tree.

8)Minimum/Maximum (BST_minimum, BST_maximum): Finds the minimum and maximum key values in the tree.

9)Successor/Predecessor (successor, predecessor): Finds the successor and predecessor of a given node in the tree.

10)Ceiling/Floor (Ceiling, Floor): Finds the smallest key greater than or equal to a given value, and the largest key less than or equal to a given value, respectively.

11)Headset/Tailset (Headset, Tailset): Prints all elements less than a given value, and all elements greater than or equal to a given value, respectively.

12)Subset (Subset): Prints all elements within a given range [j, k).

13)Size (Size): Returns the number of elements in the set.

14)Empty (Empty): Checks if the set is empty.

15)Clear (Clear): Clears all elements from the set.
