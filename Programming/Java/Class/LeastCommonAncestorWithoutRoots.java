/*	Question: Find the common ancestor with two nodes, which only give the ancester
 *	Date: 2015.05.26
 */
 
class Node
{
	public Node parent;
	public boolean traceParent(Node x)		//看该节点的若干个父亲是否为x
	{
		Node n = this.parent;
		while(n != null)
		{
			if(n == x)
				return true;
			n = n.parent;
		}
		return false;
	}
	//...
}

class LeastCommonAncestorWithoutRoots
{
	public Node algorithmn(Node a, Node b)
	{
		if(a.parent == b.parent)	//两个节点的父亲节点一样
			return a.parent;
		else if(a.traceParent(b))	//b是a的若干个parent，那么公共ancestor是b的父亲（若b是树根结点则返回null）
			return b.parent;
		else if(b.traceParent(a))
			return a.parent;		//a是b的若干个parent，那么公共ancestor是a的父亲（若a是树根结点则返回null）
		else
			return algorithmn(a.parent, b.parent);
	}
}