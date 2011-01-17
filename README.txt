// $Id: README.txt,v 1.3 2010/11/14 12:37:25 doublethink Exp $

  -----------------------------------------------------------------------------------------
																		ABOUT THE MODULE
	-----------------------------------------------------------------------------------------
	Plugin homepage: http://onehackoranother.com/projects/jquery/Tipsy/
	
	Tipsy module provides a Facebook-like balloon tooltip for any element you like on the
	page, it integrates Tipsy jquery plugin (https://github.com/jaz303/Tipsy) by Jason Frame.
	The module is an integration contributed to Drupal by wikikiwis team (http://wikikiwis.com).
	
	Currently, this module allows tooltips to appear with a textarea, a textfield, or any 
	other HTML attribute specified in Tipsy settings page.
	
	It supplies hover, or focus states, and comes with a bunch of options that is specified
	in the settings page, without the need to dive into jQuery at all.
	
	-----------------------------------------------------------------------------------------
																		HOW TO USE TIPSY
	-----------------------------------------------------------------------------------------
	First the modules must be enabled admin/build/modules page.
	
	Then go to admin/settings/Tipsy to specify and customize Tipsy settings, you will notice that
	you have the option to enable Tipsy on all Drupal forms descriptions inside your site.
	You also have have to specify the position where Tipsy must appear, the delay of the appear and
	disappear in milliseconds, how Tipsy is triggered (hover/focus), the opacity of the tooltip,
	and the offset (number of pixels between the tooltip and the element).
	
	CUSTOM SELECTORS
	--------------------------------
	In this section you can specify any CSS selectors to apply Tipsy to it.
	The example below applies Tipsy tooltips anchor title on primary navigation inside Drupal site
	
	1) Our CSS selector will be => "li.leaf a" (without quotes) which means any anchor inside the li
	   that has the class leaf.
	   
	2) Specify the options that best suits your selector.
	
	3) Tooltip content will be the "title" (without quotes) of the anchor that will appear inside 
	   the Tipsy tooltip (See below for other usage: TOOLTIP CONTENT)
	   	   
	4) Save your settings.
	
	Note that you can add as many selectors as needed, to DELETE a selector you only have to 
	REMOVE/EMPTY its selector textfield and SAVE.
	
	TOOLTIP CONTENT
	--------------------------------
	In this field you can provide the HTML attribute of the desired content of Tipsy tooltip, or 
	any jQuery/JavaScript function that returns any value you wish.
	
	Examples:
	  1) Use the following to return the ID of the HTML element: id
	  
	  2) Use the following to return the anchor of an a tag: href
	
	  3) You can write the below function inside the Tooltip content textarea to make the content 
	     of the "title" attribute formatted uupercase.
	       
	       function() { return $(this).attr('original-title').toUpperCase(); }
	     
	  4) You can write the below function inside the Tooltip content textarea to return a custom 
	     content of your choice.
	      
	       function() { return 'My custom tooltip content'; }
	       
	       