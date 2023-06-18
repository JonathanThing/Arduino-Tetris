import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

import javax.sound.midi.InvalidMidiDataException;
import javax.sound.midi.MidiEvent;
import javax.sound.midi.MidiMessage;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.Sequence;
import javax.sound.midi.Track;

public class MidiReader {
    public static final int NOTE_ON = 0x90;
    public static final int NOTE_OFF = 0x80;

    public static void main(String[] args) throws InvalidMidiDataException, IOException {

        String fileName;
        String outputFileName;
        Scanner scanner = new Scanner(System.in);
        PrintWriter cppWriter = null;
        PrintWriter headerWriter = null;
        File midiFile = null;
        File outputCppFile = null;
        File outputHeaderFile = null;
        Sequence sequence = null;

        int freq[][];
        int time[][];

        int pins[];
        int trackLength[];

        while (true) {
            System.out.print("Input name of midi file: ");
            fileName = scanner.nextLine();
            try {
                midiFile = new File("./MidiFiles/" + fileName + ".mid");
            } catch (Exception exception) {
                System.out.println("Error Reading File: " + exception);
                continue;
            }
            break;
        }

        System.out.print("Input Name Of Header File: ");
        outputFileName = scanner.nextLine();
        if (new File("./TETRIS/" + outputFileName + ".h").exists()) {
            System.out.print(outputFileName + ".h already exists. Rewrite file? (y/n): ");
            if (!scanner.nextLine().equals("y")) {
                System.exit(1);
            }
        }
        outputHeaderFile = new File("./TETRIS/" + outputFileName + ".h");
        outputCppFile = new File("./TETRIS/" + outputFileName + ".cpp");
        try {
            headerWriter = new PrintWriter(outputHeaderFile);
            cppWriter = new PrintWriter(outputCppFile);
        } catch (Exception e) {
            System.out.println("Printer Writer Failed");
            e.printStackTrace();
        }

        sequence = MidiSystem.getSequence(midiFile);

        int numberOfTracks = sequence.getTracks().length;
        Track tracks[] = sequence.getTracks();
        pins = new int[numberOfTracks];
        trackLength = new int[numberOfTracks];

        freq = new int[numberOfTracks][];
        time = new int[numberOfTracks][];

        double timePerTick = (sequence.getMicrosecondLength() / 1000.0) / (sequence.getTickLength());

        headerWriter.println("#ifndef " + outputFileName + "H");
        headerWriter.println("#define " + outputFileName + "H");
        headerWriter.println("#include \"MusicTrack.h\"");
        headerWriter.println("#include \"Arduino.h\"");
        headerWriter.println("#define NUMBER_OF_TRACKS " + numberOfTracks);
        headerWriter.println("extern MusicTrack tracks" + outputFileName + "[];\n#endif");

        cppWriter.println("#include \"MenuMusic.h\"");

        for (int i = 0; i < numberOfTracks; i++) {
            System.out.print("Buzzer Pin for track " + (i + 1) + ": ");
            pins[i] = scanner.nextInt();
            trackLength[i] = tracks[i].size();
            freq[i] = new int[trackLength[i]];
            time[i] = new int[trackLength[i]];
            for (int j = 0; j < trackLength[i]; j++) {
                MidiEvent event = tracks[i].get(j);
                MidiMessage message = event.getMessage();
                int noteStatusByte = message.getMessage()[0] & 0xFF;
                if (0x80 <= noteStatusByte && noteStatusByte < 0x90) {
                    freq[i][j] = 0;
                } else if (0x90 <= noteStatusByte && noteStatusByte < 0xA0) {
                    int noteNumber = message.getMessage()[1] & 0xFF;
                    freq[i][j] = (int) ((Math.pow(2.0, (noteNumber - 69.0) / 12.0)) * 440.0);
                }

                time[i][j] = (int) (event.getTick() * timePerTick);
            }

            // Remove leading zeros in freq
            for (int j = 0; j < trackLength[i]; j++) {
                if (freq[i][j] != 0) {
                    freq[i] = Arrays.copyOfRange(freq[i], j, trackLength[i]);
                    time[i] = Arrays.copyOfRange(time[i], j, trackLength[i]);
                    trackLength[i] -= j;
                    break;
                }
            }

        }

        for (int i = 0; i < numberOfTracks; i++) {
            cppWriter.print("const uint16_t freq" + i + "[] = { ");
            cppWriter.print(freq[i][0]);
            for (int j = 1; j < trackLength[i]; j++) {
                cppWriter.print(", " + freq[i][j]);
            }
            cppWriter.println("};");
            cppWriter.print("const uint32_t time" + i + "[] = { ");
            cppWriter.print(time[i][0]);
            for (int j = 1; j < trackLength[i]; j++) {
                cppWriter.print(", " + time[i][j]);
            }
            cppWriter.println("};");
        }

        cppWriter.println("MusicTrack tracks" + outputFileName + "[]= {");
        cppWriter.print("{" + pins[0] + ", freq0, time0, " + trackLength[0] + "}");
        for (int i = 1; i < numberOfTracks; i++) {
            cppWriter.print(",\n{" + pins[i] + ", freq" + i + ", time" + i + ", " + trackLength[i] + "}");
        }
        cppWriter.print("\n};");

        headerWriter.close();
        cppWriter.close();
    }
}