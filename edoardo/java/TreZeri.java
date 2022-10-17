import java.util.regex.*;

public class TreZeri {
    public static boolean scan(String s) {
        int state = 0;
        int i = 0;
        while (state >= 0 && i < s.length()) {
            final char ch = s.charAt(i++);
            System.out.println(ch);
            System.out.println("ok");
            switch (state) {
                case 0:
                    if (ch == '0')
                        state = 1;
                    else if (ch == '1')
                        state = 0;
                    else
                        state = -1;
                    break;
                case 1:
                    if (ch == '0')
                        state = 2;
                    else if (ch == '1')
                        state = 0;
                    else
                        state = -1;
                    break;
                case 2:
                    if (ch == '0')
                        state = 3;
                    else if (ch == '1')
                        state = 0;
                    else
                        state = -1;
                    break;
                case 3:
                    if (ch == '0' || ch == '1')
                        state = 3;
                    else
                        state = -1;
                    break;
            }
        }
        return !(state == 3);
    }

    public static void main(String[] args) {
        Pattern p = Pattern.compile(".*000.*");// . represents single character
        Matcher m = p.matcher("ciao000ciaoao");
        boolean b = m.matches();
        System.out.println(scan("ciaocomestai") ? "OK" : "NOPE");
    }
}