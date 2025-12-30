/*
Problem Overview (in simple words):

- We have a big hotel and n customers.
- Each customer comes on day `a` and leaves on day `b`.
- Every customer needs their own room.
- A room can be reused only if the previous customer leaves
  strictly before the next one arrives (b < a).

What we need:
1) The minimum number of rooms needed.
2) Which room each customer gets (in the original input order).

------------------------------------------------------------

How I thought about it:

This is basically about handling time intervals smartly.
If two stays do not overlap, they can share the same room.

To minimize the number of rooms:
- Always reuse a room as soon as it becomes free.
- If no room is free, open a new one.

So the real question becomes:
"Among all currently occupied rooms, which one gets free first?"

------------------------------------------------------------

Greedy Plan:

1) Sort customers by arrival day.
2) Keep a min-heap (priority queue) of rooms currently in use.
   Each entry stores:
     - when the room becomes free (departure day)
     - the room number

3) For every customer (in arrival order):
   - If the room with the earliest departure ends before
     this customer arrives, reuse that room.
   - Otherwise, create a new room.

Why this works:
- Reusing the earliest free room is always safe.
- It keeps future options open and guarantees the minimum
  number of rooms.

------------------------------------------------------------

Important Java Notes (to avoid TLE on CSES):
- Use fast input (byte-based scanner).
- Avoid lambdas and slow utilities.
- Build output once using StringBuilder.

------------------------------------------------------------

Time Complexity:
- Sorting: O(n log n)
- Heap operations: O(n log n)

Space Complexity:
- O(n)

*/

import java.io.*;
import java.util.*;

public class Solution2 {

    // Fast input reader (much faster than Scanner / StringTokenizer)
    static class FastScanner {
        private final byte[] buffer = new byte[1 << 16];
        private int ptr = 0, len = 0;
        private final InputStream in = System.in;

        private int readByte() throws IOException {
            if (ptr >= len) {
                len = in.read(buffer);
                ptr = 0;
                if (len <= 0) return -1;
            }
            return buffer[ptr++];
        }

        int nextInt() throws IOException {
            int c, sign = 1, val = 0;
            do {
                c = readByte();
            } while (c <= ' ');
            if (c == '-') {
                sign = -1;
                c = readByte();
            }
            while (c > ' ') {
                val = val * 10 + (c - '0');
                c = readByte();
            }
            return val * sign;
        }
    }

    // Represents one customer stay
    static class Customer implements Comparable<Customer> {
        int start, end, index;

        Customer(int s, int e, int i) {
            start = s;
            end = e;
            index = i;
        }

        // Sort by arrival day
        public int compareTo(Customer other) {
            return Integer.compare(this.start, other.start);
        }
    }

    // Represents a room currently in use
    static class Room implements Comparable<Room> {
        int endTime, roomNo;

        Room(int e, int r) {
            endTime = e;
            roomNo = r;
        }

        // Room with earlier ending time comes first
        public int compareTo(Room other) {
            return Integer.compare(this.endTime, other.endTime);
        }
    }

    public static void main(String[] args) throws Exception {
        FastScanner fs = new FastScanner();
        int n = fs.nextInt();

        Customer[] customers = new Customer[n];

        for (int i = 0; i < n; i++) {
            int a = fs.nextInt();
            int b = fs.nextInt();
            customers[i] = new Customer(a, b, i);
        }

        // Sort customers by arrival time
        Arrays.sort(customers);

        // Min-heap of rooms by earliest departure
        PriorityQueue<Room> pq = new PriorityQueue<>();

        int[] result = new int[n];
        int roomsUsed = 0;

        for (Customer c : customers) {
            // If a room is free, reuse it
            if (!pq.isEmpty() && pq.peek().endTime < c.start) {
                Room r = pq.poll();
                result[c.index] = r.roomNo;
                r.endTime = c.end;
                pq.add(r);
            } else {
                // Otherwise, open a new room
                roomsUsed++;
                result[c.index] = roomsUsed;
                pq.add(new Room(c.end, roomsUsed));
            }
        }

        // Output
        StringBuilder sb = new StringBuilder();
        sb.append(roomsUsed).append('\n');
        for (int i = 0; i < n; i++) {
            sb.append(result[i]).append(' ');
        }

        System.out.print(sb);
    }
}
