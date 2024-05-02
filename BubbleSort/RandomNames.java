import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/*
	RANDOM NAME GENERATOR
	by Geoff Draper
	for use by the students of CS301
*/

public class RandomNames {

    private final char consenants[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'r', 's', 't', 'v', 'w', 'x', 'z'};
    private final char vowels[] = {'a', 'e', 'i', 'o', 'u', 'y'};
    private final String fnames[] = {
            "Gurthark", "Frobwit", "Belwit", "Dirin", "Althia", "Zilbo", "Entharian", "Grueslayer", "Borphee",
            "Ryker", "Duncanthrax", "Timberthrax", "Mumberthrax", "Idwit", "Oogle", "Wurb", "Dimmy", "Megaboz",
            "Orkan", "Thriff", "Accardi", "Antharion", "Grubbo", "Boswell", "Barwell", "Pheebor", "Bor", "Phee",
            "Frobozz", "Quendor", "Lim", "Mysterion", "Frotzen", "Nitfol", "Gondor", "Violet", "Gaspar", "Woomax",
            "Y'Gael", "Krill", "Bivotar", "Juranda", "Belboz", "Alexis", "Trembyle", "Morphius", "Molly",
            "Moodock", "Canuk", "Yannick", "Dalboz", "Griff", "Zylon", "Bozbo", "Harmonius", "Fzort", "Thaddium",
            "Mumbo", "Phloid", "Loowit", "Duncwit", "Barbawit", "Syovar", "Amathradonis", "Jeearr", "Rezrov"

    };
    private final String jobs[] = {
            "Programmer", "Accountant", "Project Manager", "Graphic Designer", "Tester", "Systems Administrator",
            "Analyst", "Technician", "Engineer", "Custodian", "Consierge", "Director", "Consultant", "Bookkeeper",
            "Physicist", "Granola Taster", "Blacksmith", "Game Show Host", "Granola Miner", "Granola Smelter"
    };
    private List<String> IDs;;

    public RandomNames(int n, int q) {
        IDs = new ArrayList<String>(n);
        for (int i=1; i<=n; i++) {
            IDs.add(""+i);
        }

        String filename = "roster" + n + ".txt";
        try (FileWriter fw = new FileWriter(filename)) {
            //write the "roster" section of the file
            fw.write(n + "\n");
            for (int i=0; i<n; ++i) {
                fw.write(randomFirstName() + " " + randomLastName() + "|");
                fw.write(randomID() + "|");
                int age = 20 + (int)(Math.random() * 45);
                fw.write(age + "|");
                fw.write(randomJob() + "|");
                fw.write("" + randomYear(age));
                fw.write("\n");
            }
            //write the "query" section of the file
//            fw.write(q + "\n");
//            for (int i=0; i<q; i++) {
//                fw.write(((int)(Math.random()*n+1)) + "\n");
//            }
//            fw.write("\n");
            System.out.println("Output written to " + filename);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private String randomID() {
        int i = (int)(Math.random()*IDs.size());
        String id = IDs.get(i);
        IDs.remove(i);
        return id;
    }

    private String randomLastName() {
        int len = 4 + (int)(Math.random()*5);
        String name = "";
        for (int i=0; i<len; i+=2) {
            char con = consenants[(int)(Math.random()*consenants.length)];
            char vow = vowels[(int)(Math.random()*vowels.length)];
            if (i==0) {
                con = Character.toUpperCase(con);
            }
            name += con;
            name += vow;
        }
        return name;
    }

    private String randomFirstName() {
        return fnames[(int)(Math.random() * fnames.length)];
    }

    private String randomJob() {
        return jobs[(int)(Math.random() * jobs.length)];
    }

    private int randomYear(int age) {
        return (2021-(age-20) + (int)(Math.random()*(age-20)));
    }

    private static void usage() {
        //System.err.println("USAGE: java RandomNames N Q (where N is how many records you want to generate and Q is the number of queries; both must be non-negative)");
        System.err.println("USAGE: java RandomNames N (where N is how many records you want to generate; must be non-negative)");
    }


    public static void main(String[] args) {
        if (args.length < 1 /*2*/) {
            usage();
        } else {
            try {
                int n = Integer.parseInt(args[0]);
                int q = 0;//Integer.parseInt(args[1]);
                if (n >= 0 && q >= 0) {
                    new RandomNames(n,q);
                } else {
                    usage();
                }
            } catch (NumberFormatException e) {
                usage();
            }
        }
    }
}
