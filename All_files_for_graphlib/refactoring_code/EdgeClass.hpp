using namespace std;

template<typename T, typename W>
class Edge
{
    private:
        T src;
        T dest;
        W  weight;
    public:
        Edge(T _src, T _dest, W _weight)
        {
            this->src = _src;
            this->dest = _dest;
            this->weight = _weight;
        }

        T getSource() const
        {
            return this->src;        
        }

        T getDestination() const
        {
            return this->dest;
        }

        W getWeight() const
        {
            return this->weight;
        }
};
