import java.io.*;
import java.util.*;

class HuffmanNode implements Comparable<HuffmanNode> , Serializable{
    char data;
    int frequency;
    HuffmanNode left, right;

    public HuffmanNode(char data, int frequency) {
        this.data = data;
        this.frequency = frequency;
    }

    @Override
    public int compareTo(HuffmanNode node) {
        return this.frequency - node.frequency;
    }
}

public class HuffmanCoding {
    private static Map<Character, String> huffmanCodes = new HashMap<>();

    public static void main(String[] args) {
        String inputFileName = "道路以目.txt";
        String compressedFileName = "compressed.bin";
        String decompressedFileName = "decompressed.txt";

        try {
            // Step 1: Read the input file and build the Huffman tree
            String fileContent = readFile(inputFileName);
            HuffmanNode root = buildHuffmanTree(fileContent);

            // Step 2: Generate Huffman codes for each character
            generateHuffmanCodes(root, "");

            // Step 3: Compress the file and save the Huffman tree
            compressFile(fileContent, compressedFileName, root);

            // Step 4: Decompress the file using the saved Huffman tree
            decompressFile(compressedFileName, decompressedFileName, root);

            //System.out.println("Huffman Coding completed successfully!");
            System.out.println("success!");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static String readFile(String fileName) throws IOException {
        // Read the content of the file
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        StringBuilder content = new StringBuilder();
        int c;
        while ((c = reader.read()) != -1) {
            content.append((char) c);
        }
        reader.close();
        return content.toString();
    }

    private static HuffmanNode buildHuffmanTree(String data) {
        // Build the Huffman tree from the input data
        Map<Character, Integer> frequencyMap = new HashMap<>();
        for (char c : data.toCharArray()) {
            frequencyMap.put(c, frequencyMap.getOrDefault(c, 0) + 1);
        }

        PriorityQueue<HuffmanNode> priorityQueue = new PriorityQueue<>();
        for (Map.Entry<Character, Integer> entry : frequencyMap.entrySet()) {
            priorityQueue.add(new HuffmanNode(entry.getKey(), entry.getValue()));
        }

        while (priorityQueue.size() > 1) {
            HuffmanNode left = priorityQueue.poll();
            HuffmanNode right = priorityQueue.poll();
            HuffmanNode parent = new HuffmanNode('\0', left.frequency + right.frequency);
            parent.left = left;
            parent.right = right;
            priorityQueue.add(parent);
        }

        return priorityQueue.poll();
    }

    private static void generateHuffmanCodes(HuffmanNode root, String code) {
        // Generate Huffman codes for each character
        if (root != null) {
            if (root.left == null && root.right == null) {
                huffmanCodes.put(root.data, code);
            }
            generateHuffmanCodes(root.left, code + "0");
            generateHuffmanCodes(root.right, code + "1");
        }
    }

    private static void compressFile(String data, String compressedFileName, HuffmanNode root) throws IOException {
        // Compress the file and save the Huffman tree
        BitOutputStream bitOutputStream = new BitOutputStream(new FileOutputStream(compressedFileName));
        ObjectOutputStream objectOutputStream = new ObjectOutputStream(new FileOutputStream(compressedFileName + ".tree"));
        objectOutputStream.writeObject(root);

        for (char c : data.toCharArray()) {
            String code = huffmanCodes.get(c);
            for (char bit : code.toCharArray()) {
                bitOutputStream.write(bit == '1');
            }
        }

        bitOutputStream.close();
        objectOutputStream.close();
    }

    private static void decompressFile(String compressedFileName, String decompressedFileName, HuffmanNode root) throws IOException {
        // Decompress the file using the saved Huffman tree
        BitInputStream bitInputStream = new BitInputStream(new FileInputStream(compressedFileName));
        ObjectInputStream objectInputStream = new ObjectInputStream(new FileInputStream(compressedFileName + ".tree"));

        try {
            root = (HuffmanNode) objectInputStream.readObject();
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        StringBuilder decompressedData = new StringBuilder();
        HuffmanNode current = root;
        while (bitInputStream.hasNextBit()) {
            boolean bit = bitInputStream.readBit();
            current = bit ? current.right : current.left;
            if (current.left == null && current.right == null) {
                decompressedData.append(current.data);
                current = root;
            }
        }

        bitInputStream.close();
        objectInputStream.close();

        // Write the decompressed data to a new file
        BufferedWriter writer = new BufferedWriter(new FileWriter(decompressedFileName));
        writer.write(decompressedData.toString());
        writer.close();
    }

    // Helper class to handle bit-level input
    private static class BitInputStream {
        private FileInputStream input;
        private int currentByte;
        private int currentBit;

        public BitInputStream(FileInputStream input) {
            this.input = input;
            this.currentByte = 0;
            this.currentBit = 7;
        }

        public boolean hasNextBit() throws IOException {
            if (currentBit < 0) {
                currentByte = input.read();
                currentBit = 7;
            }
            return currentByte != -1;
        }

        public boolean readBit() throws IOException {
            if (!hasNextBit()) {
                throw new EOFException();
            }
            boolean bit = ((currentByte >> currentBit) & 1) == 1;
            currentBit--;
            return bit;
        }

        public void close() throws IOException {
            input.close();
        }
    }

    // Helper class to handle bit-level output
    private static class BitOutputStream {
        private FileOutputStream output;
        private int currentByte;
        private int currentBit;

        public BitOutputStream(FileOutputStream output) {
            this.output = output;
            this.currentByte = 0;
            this.currentBit = 7;
        }

        public void write(boolean bit) throws IOException {
            if (bit) {
                currentByte |= (1 << currentBit);
            }
            currentBit--;
            if (currentBit < 0) {
                output.write(currentByte);
                currentByte = 0;
                currentBit = 7;
            }
        }

        public void close() throws IOException {
            while (currentBit >= 0) {
                output.write(currentByte);
                currentBit--;
            }
            output.close();
        }
    }
}
