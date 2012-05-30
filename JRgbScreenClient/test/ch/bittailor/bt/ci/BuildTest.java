package ch.bittailor.bt.ci;

import static org.junit.Assert.*;

import java.util.SortedSet;
import java.util.TreeSet;

import org.junit.Test;

public class BuildTest {

	private Build mGood   = new Build("log20120419085114Lbuild.136.xml");
	private Build mFailed = new Build("log20120405135316.xml");
	
	@Test
	public void testGetStatus() {
		assertEquals(IBuild.Status.GOOD, mGood.getStatus());
		assertEquals(IBuild.Status.FAILED, mFailed.getStatus());
	}

	@Test
	public void testGetId() {
		assertEquals(20120419085114L, mGood.getId());
		assertEquals(20120405135316L, mFailed.getId());
	}

	@Test
	public void testCompareToInOrder() {
		SortedSet<IBuild> treeSet = new TreeSet<IBuild>();
		treeSet.add(mGood);
		treeSet.add(mFailed);
		
		assertEquals(mGood,treeSet.first());
		assertEquals(mFailed,treeSet.last());

	}

	@Test
	public void testCompareToOutOffOrder() {
		SortedSet<IBuild> treeSet = new TreeSet<IBuild>();
		treeSet.add(mFailed); 
		treeSet.add(mGood);
		
		assertEquals(mGood,treeSet.first());
		assertEquals(mFailed,treeSet.last());
	}
	
}
