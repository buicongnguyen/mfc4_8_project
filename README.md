# mfc4_8_project
Project requirements:  
	. Can use 1 dialog which has image.
		Draw a circle in this dialog. 
	. User have one Edit box to input the radius of Circle 
	. A button to redraw the Circle with given radius. 
	. Draw the circle with given radius: the ring with yellow color. 
	. Draw a cross mark in center mass of the Circle. 

Project requirements break down, then implement step by step.  
	break down step: 
	. background is black. 
		put a function in the main dialog: access the member variable 
		Add random value -> random sky. 
		. set random noise for all picture. 
		. change to get the random noise value from 100 to 255 
			so only bright pixel is kept. 
		 
	. paint a yellow circle with given point, given size. 
		. There is no requirement about the circle center point, 
			simplify the requirement as : center is center of the dialog 
		
	. draw the cross mark in center mass of all point in the circle.
		calculate center mass : inside a circle. 
		draw the cross mask with red color. 
	. make user input size of circle
		add edit box 
			add variable for that box. 
				set number, range for that m_editRadius
		coordinate: x, y. 
		modify code to generate that ring on the screen. 
		
		add: centerX, centerY variable;  
	
	press make circle in main dialog: 
		redraw the screen. 
