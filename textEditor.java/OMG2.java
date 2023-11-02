//代码整体布局是
//前面是向容器里添加组件
//中间是为组件添加监听器
//后面是一些功能函数
//导入所需的包
import java.util.Calendar;
import java.awt.MenuBar;
import java.awt.Menu;
import java.awt.Frame;
import java.awt.Button;
import java.awt.TextArea;
import java.awt.Dialog;
import java.awt.MenuItem;
import java.awt.Color;
import java.awt.FileDialog;
import java.awt.Label;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.awt.event.MouseMotionListener;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.MouseEvent;


public class OMG2 implements MouseMotionListener,ActionListener{
    //定义变量
    private TextArea ta;
    private String s = "";
    private String s7="";
    private String s8="";
    private Frame fr;
    private Dialog d;
    private Button b1;
    private Button b2;
    private Button b3;
    private Button b4;
    private Calendar cal;
    private int tongji1;
    private int tongji2;
    private char[] shuzu;
    //构造方法
    public OMG2() {
        //从第48行到第94行都是向BorderLayout容器里添加组件
        Frame fr = new Frame("文本编辑器");
        TextArea ta = new TextArea();
        MenuBar mb = new MenuBar();
        Menu m1 = new Menu("文件");
        Menu m2 = new Menu("编辑");
        Menu m3 = new Menu("帮助");
        Menu m4 = new Menu("工具栏");
        MenuItem mi1 = new MenuItem("保存");
        MenuItem mi2 = new MenuItem("新建");
        MenuItem mi3 = new MenuItem("退出");
        MenuItem mi4 = new MenuItem("展示帮助文档");
        MenuItem mi5 = new MenuItem("打开");
        MenuItem mi6 = new MenuItem("页面设置");
        MenuItem mi7 = new MenuItem("时间和日期");
        MenuItem mi8 = new MenuItem("复制");
        MenuItem mi9 = new MenuItem("粘贴");
        MenuItem mi10 = new MenuItem("剪贴");
        MenuItem mi11 = new MenuItem("撤销");
        MenuItem mi12 = new MenuItem("删除");
        MenuItem mi13 = new MenuItem("Web工具");
        MenuItem mi14 = new MenuItem("绘图");
        MenuItem mi15 = new MenuItem("自定义");
        MenuItem mi16 = new MenuItem("统计");
        m1.add(mi1);
        m1.add(mi2);
        m1.add(mi5);
        m1.add(mi3);
        m1.add(mi6);
        m2.add(mi7);
        m2.add(mi8);
        m2.add(mi9);
        m2.add(mi10);
        m2.add(mi11);
        m2.add(mi12);
        m2.add(m4);
        m3.add(mi4);
        m4.add(mi13);
        m4.add(mi14);
        m4.add(mi15);
        m4.add(mi16);
        mb.add(m1);
        mb.add(m2);
        mb.add(m3);
        Button b1 = new Button("红色");
        Button b2 = new Button("黄色");
        Button b3 = new Button("蓝色");
        Button b4 = new Button("绿色");
        //MenuItem，Menu，MenuBar，Frame这三者关系为
        //MenuItem通常加到Menu里面，Menu必须加到MenuBar里面，MenuBar必须加到Frame里面
        fr.setMenuBar(mb);
        //设置组件TaxtArea为可编辑的
        ta.setEditable(true);
        //通过接口为组件TextArea添加鼠标移动监听器
        ta.addMouseMotionListener(this);
        //通过事件适配器为组件TextArea添加键盘敲击器
        ta.addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                System.out.println("key Pressed");
            }
            public void keyReleased(KeyEvent e) {
                System.out.println("key Released");
            }
            public void keyTyped(KeyEvent e) {
                s = s + e.getKeyChar();
            }
        });
        //为菜单项mi1(保存)添加动作监听器
        mi1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                System.out.println("您正在保存文件，请稍后");
                try {
                    //跳转到第294行的baocun()函数
                    baocun();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        });
        //为菜单项mi2(新建)添加动作监听器
        mi2.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                System.out.println("正在新建文本文件，请稍后");
                try {
                    //xinjian()函数对应第281行
                    xinjian();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }});
        //为菜单项mi3(退出)添加动作监听器
        mi3.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                //用户点击这个MenuItem就退出程序
                System.out.println("您已成功退出");
                System.exit(1);
            }
        });
        //为菜单项mi4(展示帮助文档)添加动作监听器
        mi4.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                //向组件TextArea写
                ta.setText("这是个文本编辑器 \n你可以把你想写的写到下面那个绿色区域\n\n这个文本编辑器的功能有:\n"+
                        "1.可以新建文本文件\n2.可以进行页面设置\n3.可以查看帮助内容\n4.可以删除你所写的\n5.可以查看当前系统时间\n"+
                        "6.可以打开文本文件\n7.可以保存文本文件\n8.系统会监控你在这个编辑器上的所有行为\n9.可以计数你所输入的字母和数字的个数"+
                        "\n\n注意事项\n新建的文本文件的位置在D://自己的软件//66.txt\n这是我自己设置的，你的电脑可能没有这个目录\n"
                        + "当你获取源代码后请自行修改，否则会引发异常");
            }
        });
        //为菜单项mi5(打开)添加动作监听器
        mi5.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    //跳转函数dakai()，在第257行
                    //该函数返回了一个String类型的值
                    s8 = dakai();
                    //把该函数返回的这个值写到TextArea里
                    ta.setText(s8);
                } catch (FileNotFoundException e1) {
                    e1.printStackTrace();
                }
            }});
        //为菜单项mi6(页面设置)添加动作监听器
        mi6.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                //跳转函数yemiansheji()，在第315行
                yemianshezhi();
            }
        });
        //为容器Frame添加窗口监听器
        fr.addWindowListener(new WindowAdapter() {
            public void windowOpened(WindowEvent e) {
                System.out.println("window open");
            }
            public void windowClosing(WindowEvent e) {
                System.exit(1);
            }
            public void windowIconified(WindowEvent e) {
                System.out.println("window Iconified");
            }
            public void windowDeiconified(WindowEvent e) {
                System.out.println("window Deiconified");
            }
            public void windowActivated(WindowEvent e) {
                System.out.println("window Activated");
            }
            public void windowDeactivated(WindowEvent e) {
                System.out.println("window Deactivated");
            }
        });
        //为菜单项mi7(时间和日期)添加动作监听器
        mi7.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                //实例化一个Calendar对象
                //这个Calendar在java.unit包里，它和系统时间相关
                Calendar cal = Calendar.getInstance();
                //获取当前系统的年份
                int y = cal.get(Calendar.YEAR);
                //获取当前系统的月份
                int m = cal.get(Calendar.MONTH);
                int d = cal.get(Calendar.DATE);
                int h = cal.get(Calendar.HOUR_OF_DAY);
                int mi = cal.get(Calendar.MINUTE);
                int s = cal.get(Calendar.SECOND);
                String t = "现在时刻是"+y+"年"+m+"月"+d+"日"+h+"时"+mi+"分钟"+s+"秒";
                ta.setText(t);
            }
        });
        //为菜单项mi12(删除)添加动作监听器
        mi12.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                //删除其实就是用一个空字符串代替你所写的
                String t1 = "";
                ta.setText(t1);
            }
        });
        //为菜单项mi16(统计)统计动作监听器
        mi16.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                //tongji()函数在第238行
                tongji();
                ta.setText("你所输入字母的个数是:"+tongji1+"\n你所输入数字的个数是:"+tongji2);
            }
        });
        //向Frame添加组件TextArea
        fr.add(ta);
        //设置容器Frame是可见的
        fr.setVisible(true);
        //设置容器的左上角的位置和容器本身的大小
        fr.setBounds(100,100,400,400);
    }

    public static void main(String[] args) {
        OMG2 o = new OMG2();
    }

    public void tongji() {
        //统计用户输入的数字个数和字母个数
        //现把用户输入的存到数组里
        char[] shuzu = s.toCharArray();
        for(int i=0;i<shuzu.length;i++) {
            //如果是字母
            if((shuzu[i]<=122)&&(shuzu[i]>=97)) {
                tongji1 = tongji1 + 1;
            }
            //如果是数字
            if((shuzu[i]>=49)&&(shuzu[i]<=57)) {
                tongji2 = tongji2 + 1;
            }
        }
    }
    //根据你的输入打开一个文本文件
    public String dakai() throws FileNotFoundException {
        //使用组件FileDialog，然后使用函数getFile和获取输入的文件名
        FileDialog fd = new FileDialog(fr,"打开",FileDialog.LOAD);
        fd.setVisible(true);
        //如果你没有输入文件名
        if(fd.getFile()==null) {
            System.out.println("打开失败");
        }
        try {
            //获取你输入文件名的路径，并将它作为参数传递给流FileInputStream，把这个流作为参数传递给流InputStreamReader
            FileInputStream fis1 = new FileInputStream(fd.getDirectory()+fd.getFile());
            InputStreamReader isr1 = new InputStreamReader(fis1);
            //定义一个数组，这个数组存了你所输入那个文件的内容
            char[] cbuf = new char[10];
            isr1.read(cbuf, 0, 10);
            for(int j=0;j<10;j++) {
                s7 = s7 + cbuf[j];
            }
        }catch(Exception e) {
            System.out.println("打开异常");
        }
        //返回你所输入文件里的内容，并显示在TextArea里面
        return s7;
    }
    public void xinjian() throws IOException {
        //这里我选择在D://自己的软件这个目录下新建一个文本文件66.txt
        String s = "D://自己的软件";
        String p = "66.txt";
        File f = new File(s,p);
        if(!f.exists()) {
            //新建文件的专属函数creatNewFile()
            f.createNewFile();
            System.out.println("新建成功");
            System.out.println("新建文本文件的位置："+f.getPath());
        }
    }
    //将你在TextArea里面所写的保存到一个文本文件里
    public void baocun() throws IOException,NullPointerException {
        FileDialog fd = new FileDialog(fr,"请输入你要保存的文件名",FileDialog.SAVE);
        System.out.println("你在TextArea里的输入为:"+s);
        fd.setVisible(true);
        if(fd.getDirectory()==null) {
            System.out.println("你没有选择保存位置");
        }
        try {
            FileOutputStream fos = new FileOutputStream(fd.getDirectory() + fd.getFile());
            OutputStreamWriter osw = new OutputStreamWriter(fos);
            osw.write(s);
            osw.flush();
            osw.close();
            fos.close();
        }catch(Exception e) {
            System.out.println("保存异常");
        }finally {
            System.out.println("您的内容保存到了:"+fd.getDirectory()+fd.getFile());
        }
    }
    //页面设计设计的是Dialog,你按不同的按钮页面会变成不同的颜色
    public void yemianshezhi() {
        Dialog d;
        d = new Dialog(fr,"页面设置",true);
        d.setBounds(200,200,400,500);
        Label l = new Label("设置背景颜色，只需点击对应的按钮即可设置成相应的颜色");
        Button b1 = new Button("红色");
        Button b2 = new Button("黄色");
        Button b3 = new Button("蓝色");
        Button b4 = new Button("绿色");
        d.add(l,"North");
        d.add(b1,"Center");
        d.add(b2,"East");
        d.add(b3,"South");
        d.add(b4,"West");
        d.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(1);
            }
        });
        b1.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                b1.setBackground(Color.RED);
            }
        });
        b2.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                b2.setBackground(Color.YELLOW);
            }
        });
        b3.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                b3.setBackground(Color.BLUE);
            }
        });
        b4.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                b4.setBackground(Color.GREEN);
            }
        });
        d.setVisible(true);
    }
    public void actionPerformed(ActionEvent e) {
        System.exit(1);
    }
    @Override
    public void mouseDragged(MouseEvent e) {
        System.out.println("mouse Dragged");
    }
    @Override
    public void mouseMoved(MouseEvent e) {
    }
}
