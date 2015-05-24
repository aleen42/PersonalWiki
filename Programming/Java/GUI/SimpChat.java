package com.Simp;

import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import com.java.ui.componentc.JCTextField;
import com.sun.awt.AWTUtilities;

public class SimpChat extends JFrame
{
	
	private JPanel contentPane;
	private int point_x, point_y;
	private boolean isDragging = false;
	private boolean isUserListShown = false;
	private DataBase db = new DataBase();
	JButton Add_Button;
	
	public JButton Close_Button;
	public UserList userlist;
	private JLabel error_label;
 	public JLabel Name_Label;
	public JLabel IPV4_Label;
	private JLabel Status_Label;
	private JPanel Add_user_panel;
	private JTextField User_name_textbox;
	private JTextField Ip_textbox;
	private String User_name_textbox_text_value = "";
	private String Ip_textbox_text_value = "";
	
//	private TrayIcon trayIcon = null; // Icon
//	private SystemTray tray = null; // Task Bar

	

	/**
	 * Create the frame.
	 */
	public SimpChat(String User_type) 
	{
		OptimalFont.setUI();	//抗锯齿字体
		setUndecorated(true);	 																	//Without Border
		AWTUtilities.setWindowOpaque(this, false);													//Set Background Opaque to false
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Dimension scrSize = Toolkit.getDefaultToolkit().getScreenSize();  							//Get the size of current screen
		setBounds(0, 0, (int)(scrSize.width * 0.8), (int)(scrSize.height * 0.9));	
		setLocation((scrSize.width - getWidth()) / 2, (scrSize.height - getHeight()) / 2);			//Startup location set at the center of current screen 
		
		/* Background */
		Image bg = this.getToolkit().getImage("./Pic/bg.png");										//Set a JPanel with a background
		contentPane = new Background(bg);
		contentPane.setOpaque(false);
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		/* Add_User_Panel */
        Image adduserPanel_bg = this.getToolkit().getImage("./Pic/AddUserPanel_bg.png");
		Add_user_panel = new UIPanel(adduserPanel_bg);
		Add_user_panel.setBounds(525, 418, 514, 192);
		Add_user_panel.setVisible(false);
		getContentPane().add(Add_user_panel);
		
		/* User_name_textbox */
		User_name_textbox = new JCTextField();
		User_name_textbox.setFont(new Font("Microsoft JhengHei UI", Font.PLAIN, 13));
		User_name_textbox.setBounds(101, 23, 382, 24);
		User_name_textbox.getDocument().addDocumentListener(new DocumentListener(){		//Listen to the input
        	public void insertUpdate(DocumentEvent e) 
        	{
        		error_label.setVisible(Check_name_input(User_name_textbox_text_value = User_name_textbox.getText()));
        		Add_Button.setEnabled(Check_database());
            }

            public void removeUpdate(DocumentEvent e) 
            {
            	error_label.setVisible(Check_name_input(User_name_textbox_text_value = User_name_textbox.getText()));
            	Add_Button.setEnabled(Check_database());
            }
        	
        	public void changedUpdate(DocumentEvent e)
        	{
        		error_label.setVisible(Check_name_input(User_name_textbox_text_value = User_name_textbox.getText()));
        		Add_Button.setEnabled(Check_database());
            }
        });
		Add_user_panel.add(User_name_textbox);
		
		/* Ip_textbox */
		Ip_textbox = new JCTextField();
		Ip_textbox.setFont(new Font("Microsoft JhengHei UI", Font.PLAIN, 13));
		Ip_textbox.setBounds(100, 57, 382, 24);
		Ip_textbox.getDocument().addDocumentListener(new DocumentListener(){		//Listen to the input
        	public void insertUpdate(DocumentEvent e) 
        	{
        		error_label.setVisible(Check_IP_input(Ip_textbox_text_value = Ip_textbox.getText()));
        		Add_Button.setEnabled(Check_database());
            }

             public void removeUpdate(DocumentEvent e) 
             {
            	 error_label.setVisible(Check_IP_input(Ip_textbox_text_value = Ip_textbox.getText()));
            	 Add_Button.setEnabled(Check_database());
             }
        	
        	public void changedUpdate(DocumentEvent e)
        	{
        		error_label.setVisible(Check_IP_input(Ip_textbox_text_value = Ip_textbox.getText()));
        		Add_Button.setEnabled(Check_database());
            }
        });
		Add_user_panel.add(Ip_textbox);
		
		/* lblUsername */
		JLabel lblUsername = new JLabel("User_name");
		lblUsername.setForeground(new Color(161, 0, 0));
		lblUsername.setFont(new Font("Microsoft JhengHei UI", Font.PLAIN, 13));
		lblUsername.setBounds(19, 25, 82, 22);
		Add_user_panel.add(lblUsername);

		/* lblIP */
		JLabel lblIP = new JLabel("IP");
		lblIP.setForeground(new Color(161, 0, 0));
		lblIP.setFont(new Font("Microsoft JhengHei UI", Font.PLAIN, 13));
		lblIP.setBounds(71, 60, 19, 22);
		Add_user_panel.add(lblIP);
		
		/* ADD_Button */
		ImageIcon addbutton_static = new ImageIcon("./Pic/addbutton_static.png");
		ImageIcon addbutton_mouseover = new ImageIcon("./Pic/addbutton_mouseover.png");
		ImageIcon addbutton_pressed = new ImageIcon("./Pic/addbutton_pressed.png");
		Add_Button = new Button(addbutton_static, addbutton_mouseover, addbutton_pressed, 1);
		Add_Button.setOpaque(false);
		Add_Button.addActionListener(new ActionListener() 
		{
			public void actionPerformed(ActionEvent arg0) 
			{
				
			}
		});
		Add_Button.setBounds(Add_user_panel.getWidth() / 2 - 120 / 2, 136, 120, 30);
		Add_Button.setEnabled(false);
		Add_user_panel.add(Add_Button);
		
		
		/* error information */ 
		error_label = new JLabel("Error: ");
		error_label.setForeground(new Color(161, 0, 0));
		error_label.setFont(new Font("Microsoft JhengHei UI", Font.PLAIN, 13));
		error_label.setBounds(19, 93, 485, 22);
		error_label.setVisible(false);
		Add_user_panel.add(error_label);
		
		/* Close Button */
		ImageIcon close_button_bg = new ImageIcon("./Pic/closebutton_static.png");
		ImageIcon close_button_mouseover = new ImageIcon("./Pic/closebutton_mouseover.png");
		ImageIcon close_button_pressed = new ImageIcon("./Pic/closebutton_pressed.png");
		
		Close_Button = new Button(close_button_bg, close_button_mouseover, close_button_pressed, 0);
		Close_Button.setOpaque(false);
		
		Close_Button.setBounds(379, 4, 28, 28);
		contentPane.add(Close_Button);
		
		/* Minimize Button */ 
		ImageIcon minimize_button_bg = new ImageIcon("./Pic/minimizebutton_static.png");
		ImageIcon minimize_button_mouseover = new ImageIcon("./Pic/minimizebutton_mouseover.png");
		ImageIcon minimize_button_pressed = new ImageIcon("./Pic/minimizebutton_pressed.png");
		JButton Minimize_Button = new Button(minimize_button_bg, minimize_button_mouseover, minimize_button_pressed, 0);
		Minimize_Button.setOpaque(false);
		Minimize_Button.addActionListener(new ActionListener() 
		{
			public void actionPerformed(ActionEvent arg0) 
			{
				setExtendedState(ICONIFIED);
//				try 
//				{
//					tray.add(trayIcon); // 将托盘图标添加到系统的托盘实例中
////					setVisible(false); // 使窗口不可视
//					dispose();
//			    } 
//				catch (AWTException e) 
//				{
//					e.printStackTrace();
//			    }
			}
		});
		Minimize_Button.setBounds(351, 4, 28, 28);
		contentPane.add(Minimize_Button);
		
		/* Title */
		JLabel Title = new JLabel();
		Title.setFont(new Font("Microsoft JhengHei UI", Font.BOLD, 60));
		Title.setForeground(new Color(161, 0, 0));
		Title.setBounds(420, 551, 185, 53);
		Title.setText(User_type);
		contentPane.add(Title);
		
		/* Name Label */
		Name_Label = new JLabel();
		Name_Label.setFont(new Font("Microsoft JhengHei UI", Font.BOLD, 40));
		Name_Label.setForeground(new Color(161, 0, 0));
		Name_Label.setBounds(48, 32, 185, 53);
		Name_Label.setVisible(false);
		contentPane.add(Name_Label);
		
		/* IPV4 Label */
		IPV4_Label = new JLabel();
		IPV4_Label.setFont(new Font("Microsoft JhengHei UI", Font.PLAIN, 17));
		IPV4_Label.setForeground(Color.BLACK);
		IPV4_Label.setBounds(48, 108, 230, 46);
		IPV4_Label.setVisible(false);
		contentPane.add(IPV4_Label);
		
		/* Status Label */
		Status_Label = new JLabel();
		Status_Label.setFont(new Font("Microsoft JhengHei UI", Font.PLAIN, 14));
		Status_Label.setForeground(Color.BLACK);
		Status_Label.setBounds(48, 65, 230, 46);
		Status_Label.setVisible(false);
		contentPane.add(Status_Label);
		
		
		/* User List */
			/* JPanel */
		Image userlist_bg = this.getToolkit().getImage("./Pic/userlist_bg.png");
		userlist = new UserList(userlist_bg, Add_user_panel, Name_Label, IPV4_Label, Status_Label, User_name_textbox);
		userlist.setBounds((int)(scrSize.width * 0.3) - 4, 30, 200, 400);
		contentPane.add(userlist);
		
			/* Button */
		ImageIcon userlist_button_bg = new ImageIcon("./Pic/userlistbutton_static.png");
		ImageIcon userlist_button_mouseover = new ImageIcon("./Pic/userlistbutton_mouseover.png");
		ImageIcon userlist_button_pressed = new ImageIcon("./Pic/userlistbutton_pressed.png");
		JButton UserList_Button = new Button(userlist_button_bg, userlist_button_mouseover, userlist_button_pressed, 1);
		UserList_Button.setOpaque(false);
		UserList_Button.addActionListener(new ActionListener() 
		{
			public void actionPerformed(ActionEvent arg0) 
			{
				Show_UserList(isUserListShown);
//				setVisible(true);	//set the Z order of JFrames
			}
		});
		UserList_Button.setBounds(379, 50, 28, 84);
		contentPane.add(UserList_Button);		
		
		
		
		/* Drag Handler */
		this.addMouseListener(new MouseAdapter() 
		{													//Getting mouse_point and judge whether it's dragging
			public void mousePressed(MouseEvent e) 
			{
			    isDragging = true;
			    point_x = e.getX();
			    point_y = e.getY();
			}
			public void mouseReleased(MouseEvent e) 
			{
			    isDragging = false;
			}
		});
		
				
		
		this.addMouseMotionListener(new MouseMotionAdapter()
		{
			public void mouseDragged(MouseEvent e) 
			{
			    if (isDragging) 
			    { 
			    	int left = getLocation().x;
			    	int top = getLocation().y;
			    	setLocation(left + e.getX() - point_x, top + e.getY() - point_y);
			    } 
			}
		}); 
		
		
//		if (SystemTray.isSupported()) 
//		{ // 如果操作系统支持托盘
//			this.tray();
//		}
	}
	
	
	public void Show_UserList(boolean isthere)
	{
		if(isthere)
			Add_user_panel.setVisible(false);
		else
			Add_user_panel.setVisible(userlist.isAddUserPanelShown);
		userlist.setVisible(!isthere);
		isUserListShown = !isthere;
		
	}
	
	private boolean Check_name_input(String input)
	{
		String regex = "[a-zA-Z]+[a-zA-Z0-9]*";
		if(User_name_textbox_text_value.isEmpty())
		{
			error_label.setText("Error: The username can not be empty!");
			return true;
		}	
		else if(!input.matches(regex))
		{
			error_label.setText("Error: You can only use alphabets or numbers with alphabets first");
			return true;
		}
		return false;
	}
	
	private boolean Check_IP_input(String input)
	{
		// 定义正则表达式
		/* Check IP */
        String regex = "^(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|[1-9])\\."
                + "(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)\\."
                + "(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)\\."
                + "(1\\d{2}|2[0-4]\\d|25[0-5]|[1-9]\\d|\\d)$";
        if(!input.matches(regex))
        {
        	error_label.setText("Error: The IP address is illegal!");
        	return true;
        }			
        return false;
	}
	
	private boolean Check_database()
	{	
		if(Check_IP_input(Ip_textbox_text_value) || Check_name_input(User_name_textbox_text_value) || User_name_textbox_text_value.length() == 0 || Ip_textbox_text_value.length() == 0)
		{
			error_label.setVisible(true);
			return false;
		}
        
        /* Check isExisted */
        if(db.Check_isExisted(User_name_textbox_text_value, Ip_textbox_text_value))
        {
        	error_label.setText("Error: The user has been existed!");
        	error_label.setVisible(true);
        	return false;
        }
        error_label.setVisible(false);
        return true;	
	}
	
	public void clear_user_info()
	{
		Name_Label.setVisible(false);
		IPV4_Label.setVisible(false);
		Status_Label.setVisible(false);
	}
}
