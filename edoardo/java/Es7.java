public class Es7 {
    public static boolean scan(String s, String nome) {
        int state = 0;
        int i = 0;
        while (state >= 0 && i < s.length()) {
            int j = i;
            final char ch = s.charAt(i++);
            final char chN = nome.charAt(j++);
            switch (state) {
                case 0:
                    if (ch == chN)
                        state = 0;
                    else
                        state = 1;
                    break;
                case 1:
                    if (ch == chN)
                        state = 1;
                    else
                        state = -1;
                    break;
            }
        }
        return state == 0 || state == 1;
    }

    public static void main(String[] args) {
        System.out.println(scan("edoaldo", "edoardo") ? "OK" : "nope");
    }
}
