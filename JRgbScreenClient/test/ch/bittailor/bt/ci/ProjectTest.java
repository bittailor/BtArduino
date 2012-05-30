package ch.bittailor.bt.ci;

import static org.easymock.EasyMock.createControl;
import static org.easymock.EasyMock.expect;
import static org.junit.Assert.*;

import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

import org.easymock.IMocksControl;
import org.junit.Before;
import org.junit.Test;

public class ProjectTest {

	private IMocksControl mocks;
	private ILogFilesCollector collector;
			
	@Before
	public void setUp() {
		mocks = createControl();
		collector = mocks.createMock(ILogFilesCollector.class);
	}
	
	@Test
	public void testGetHistrory() {
		
		String folder = "logs";
		List<String> logs1 = Arrays.asList(
				"log20110920000402Lbuild.25.xml",
				"log20111030004112.xml",
				"log20111125200128.xml",
				"log20111215234733Lbuild.56.xml",
				"log20120128234817Lbuild.66.xml",
				"log20120213202105Lbuild.74.xml",
				"log20120325054806.xml");
		
		List<String> logs2 = Arrays.asList(
				"log20110921215417Lbuild.26.xml",
				"log20111031055504.xml",
				"log20111125232808Lbuild.48.xml");
		
		expect(collector.collect(folder))
			.andReturn(logs1)
		    .andReturn(logs2);
		
		mocks.replay();
		
		Project project = new Project(folder, collector);
		
		
		Iterator<IBuild> histrory1 = project.getHistrory().iterator();
		
		assertTrue(histrory1.hasNext());
		assertEquals(20120325054806L,histrory1.next().getId());
		
		assertTrue(histrory1.hasNext());
		assertEquals(20120213202105L,histrory1.next().getId());
		
		assertTrue(histrory1.hasNext());
		assertEquals(20120128234817L,histrory1.next().getId());
		
		assertTrue(histrory1.hasNext());
		assertEquals(20111215234733L,histrory1.next().getId());
		
		assertTrue(histrory1.hasNext());
		assertEquals(20111125200128L,histrory1.next().getId());
		
		assertTrue(histrory1.hasNext());
		assertEquals(20111030004112L,histrory1.next().getId());
		
		assertTrue(histrory1.hasNext());
		assertEquals(20110920000402L,histrory1.next().getId());
		
		project.update();
		
		Iterator<IBuild> histrory2 = project.getHistrory().iterator();
		
		assertTrue(histrory2.hasNext());
		assertEquals(20111125232808L,histrory2.next().getId());
		
		assertTrue(histrory2.hasNext());
		assertEquals(20111031055504L,histrory2.next().getId());
		
		assertTrue(histrory2.hasNext());
		assertEquals(20110921215417L,histrory2.next().getId());
		
		
		mocks.verify();
	}

}
