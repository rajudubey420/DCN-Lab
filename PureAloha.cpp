using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;
namespace Test_v1
{
public class Simulation
{
    Utility utils = new Utility();
    static Random random = new Random();
    private Timer t1;
    int currentTime;
    int frameSize; //frame size in bits.
    int channelCapacity; //channel capacity in bits.
    int frameTime; //time to transmit one frame on the channel in milliseconds.
    private List<Node> nodeList;
    Node A;
    Node B;
    Node C;
    Node D;
    Node E;
    int collisions = 0;
    public Simulation()
    {
        frameSize = 10;
        channelCapacity = 100;
        frameTime = (frameSize / channelCapacity) * 100;
        nodeList = new List<Node>();
        A = new Node();
        A.stationName = "Station A";
        B = new Node();
        B.stationName = "Station B";
        C = new Node();
        C.stationName = "Station C";
        D = new Node();
        D.stationName = "Station D";
        E = new Node();
        E.stationName = "Station E";
        nodeList.Add(A);
        nodeList.Add(B);
        nodeList.Add(C);
        nodeList.Add(D);
        nodeList.Add(E);
        generateFrames(5);
        t1 = new Timer(100);
        t1.Elapsed += new ElapsedEventHandler(IntervalTimerElapsed);
        t1.Start();
    }
    protected void IntervalTimerElapsed(object sender, EventArgs e)
    {
        int framesOnChannel = 0;
        foreach (Node n in nodeList)
        {
            for (int i = 0; i < n.queue.Count; i++)
            {
                if (currentTime == n.queue[i])
                {
                    Console.WriteLine(currentTime + " " + n.stationName + " " + n.queue[i]);
                    framesOnChannel = framesOnChannel + 1;
                    collisions = collisions + 1;
                    if(framesOnChannel > 1)
                        n.queue[i] = BackOff(n) + currentTime;
                }
                else
                {
                    Console.WriteLine(currentTime);
                }
            }
        }
        currentTime++;
        if (framesOnChannel > 1)
        {
            Console.WriteLine("Frames on Channel:" + framesOnChannel + " Collision!");
        }
        else
        {
            Console.WriteLine("Frames on Channel:" + framesOnChannel);
        }
        framesOnChannel = 0;
        if (currentTime > 10)
            t1.Stop();
    }
    private void generateFrames(int load_G)
    {
        for (int i = 0; i < load_G; i++)
        {
            Node randomStation = getRandomNode();
            randomStation.queue.Add(utils.RandomNumber(0, 10));
        }
        foreach (Node n in nodeList)
        {
            n.queue.Sort();
        }
    }
    private int BackOff(Node node)
    {
        int k = node.attempts;
        if (k > 10)
            k = 10;
        int R = (int)Math.Round(Math.Pow(2, k) - 1);
        int backOffTime = random.Next(0, R) * frameTime;
        return backOffTime + (frameTime * 2);
    }
    private Node getRandomNode()
    {
        switch (random.Next(1, 6))
        {
        case 1:
            return A;
        case 2:
            return B;
        case 3:
            return C;
        case 4:
            return D;
        default:
            return E;
        }
    }
}
}
