#include <iostream>
#include <cstdlib>
#include <ctime>

   // srand(time(0)); 

using namespace std ;



struct pos
{
	int x , y ;
} ;


class stack
{
	int top ;
	pos arr[100] ;
	
	public :	
	
	stack()
	{
		top = 0 ;
	}
	
	void push( pos s )
	{
		arr[ top ] = s ;
		top++ ;
	}

	pos pop()
	{
		pos temp ;
		temp = arr[ top ] ;
		top-- ;
		return temp ;
	}

	bool empty()
	{
		return top == -1 ;
	}	

} ;	
	

class queue
{
	struct pos arr[10000] ;
	int end , front ;

	public :

	queue( )
	{
		end = 0 ;
		front = 0 ;
	}	
		
	void insert( int x1 , int y1 )
	{
		if( end >= 100 )
			cout<<"OVERFLOW!" ;
		else
		{
			pos temp ;
			temp.x = x1 ;
			temp.y = y1 ;
			arr[ end ] = temp ;
			end++ ;
		}

	}
	
	pos del( )
	{
		if( front == end )
			cout<<"UNDERFLOW!" ;
		else
		{
			pos temp = arr[ front ] ;
			front++ ;
			return temp ;
		}
			
	}

	bool empty()
	{	return front > end	;	} 

} ;

stack q ; 

class board
{

	int loc[ 100 ][ 100 ] ;
	int size ;
	pos src , dest ;

	public :
	
	board( int n , pos s , pos d)
	{
		size = n ;
		src = s ;
		dest = d ;
	}

	void fill_obs( int c )
	{
		for( int i = 0 ; i < c ; i++ )
		{
			int x = random() % size ;
			int y = random() % size ;
			//cout<<" x = "<<x<<" y = "<<y ;		
			if( ( x == src.x && y == src.y ) || ( x == dest.x && y == dest.y ) || loc[ x ][ y ] == -1 )
				i-- ;
			else
				loc[ x ][ y ] = -1 ;
		}

	}

	bool has_obs( int x , int y )
	{
		if( loc[ x ][ y ] == -1 )
			return true ;
		else
			return false ;
	}

	int get_value( int x , int y )
	{	return loc[ x ][ y ] ;		}

	void set_value( int x , int y , int v )
	{	loc[ x ][ y ] = v ;		}



	void show()
	{
		for( int i = 0 ; i < size ; i++ )
		{
			for( int j = 0 ; j < size ; j++ )
				cout<<loc[ i ][ j ]<<"\t" ;
			cout<<"\n" ;
		}
	} 
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																										

} ;	



//board b ;

void find_path( board &b , pos src , pos dest , int n , int t )
{
	
	queue to_visit ;
	to_visit.insert( src.x , src.y ) ;
	bool visited[ 100 ][ 100 ]= { false } ;
	int step = 1 ;
		visited[ src.x ][ src.y ] = true ;

	b.fill_obs( t ) ;
	while( !to_visit.empty() )
	{
		pos current = to_visit.del() ;

		if( ( current.x == dest.x ) && ( current.y == dest.y ) )
		{
			b.set_value( current.x , current.y , b.get_value( current.x , current.y ) ) ;
			break ;
		}

		if( current.x < n - 1 && !visited[ current.x + 1 ][ current.y ] && !b.has_obs( current.x + 1 , current.y ) )
		{
			to_visit.insert( current.x + 1 , current.y ) ;
			b.set_value( current.x + 1 , current.y , b.get_value( current.x , current.y ) + 1 ) ;				
			visited[ current.x + 1 ][ current.y ] = true ;
		}
		if( current.y < n - 1 && !visited[ current.x ][ current.y + 1 ] && !b.has_obs( current.x , current.y + 1 ) )
		{
			to_visit.insert( current.x , current.y + 1 ) ;
			b.set_value( current.x , current.y + 1, b.get_value( current.x , current.y ) + 1 ) ;				
			visited[ current.x ][ current.y + 1 ] = true ;
		}
		if( current.x > 0 && !visited[ current.x - 1 ][ current.y ] && !b.has_obs( current.x - 1 , current.y ) )
		{
			to_visit.insert( current.x - 1 , current.y ) ;
			b.set_value( current.x - 1 , current.y , b.get_value( current.x , current.y ) + 1 ) ;				
			visited[ current.x - 1 ][ current.y ] = true ;
		}
		if( current.y > 0 && !visited[ current.x ][ current.y - 1 ] && !b.has_obs( current.x , current.y - 1 ) )
		{
			to_visit.insert( current.x , current.y - 1 ) ;
			b.set_value( current.x , current.y - 1, b.get_value( current.x , current.y ) + 1) ;				
			visited[ current.x ][ current.y - 1 ] = true ;
		}
		


	}
	cout<<"\n";

	cout<<"Field is-\n";
	b.show();
	cout<<"\n";

}

void show_path( board & b , pos src , pos dest , int n )
{

	//cout<<dest.x<<"\t"<<dest.y<<endl; 
	pos temp ;
	if( src.x == dest.x && src.y == dest.y )
	{
		q.push( temp ) ;
	}
	else if( dest.x < n - 1 && b.get_value( dest.x + 1 , dest.y ) + 1 == b.get_value( dest.x , dest.y )  )
	{
		temp.x = dest.x + 1 ;
		temp.y = dest.y ;

		q.push( temp ) ;
		show_path( b , src , temp , n ) ;
	}
	else if( dest.y < n - 1 && b.get_value( dest.x , dest.y + 1 ) + 1 == b.get_value( dest.x , dest.y ) )
	{
		temp.x = dest.x ;
		temp.y = dest.y + 1 ;	
		q.push( temp ) ;
		show_path( b , src , temp , n ) ;
	}
	else if( dest.x >0 && b.get_value( dest.x - 1 , dest.y ) + 1 == b.get_value( dest.x , dest.y ) )
	{
		temp.x = dest.x - 1 ;
		temp.y = dest.y ;
		q.push( temp ) ;
		show_path( b , src , temp , n ) ;
	}
	else if( dest.y > 0 && b.get_value( dest.x , dest.y - 1) + 1 == b.get_value( dest.x , dest.y ) )
	{
		temp.x = dest.x ;
		temp.y = dest.y - 1 ;
		q.push( temp ) ;
		show_path( b , src , temp , n ) ;
	}
	
}
						
	
int main()
{
	srand((unsigned)time(NULL));
	int n , t ;
	pos src , dest , cur;
	cout<<"Enter size of matrix -\n";
	cin>>n;
	cout<<"Enter number of obstacles -\n";
	cin>>t;
	cout<<"Enter co- ordinates of source -\n";
	cin>>src.x>>src.y ;
	cout<<"Enter co - ordinates of destination -\n" ;
	cin>>dest.x>>dest.y;
	board b( n , src , dest ) ;
	find_path( b , src , dest , n , t ) ;
	//cout<<"reverse path"<<endl;
	show_path( b , src , dest , n ) ;
	cout<<"Path\n";
	q.pop();
	q.pop();
	while( !q.empty()  )
	{
		
		cur = q.pop() ;
		cout<<cur.x<<" , "<<cur.y<<endl ;
	}
	cout<<dest.x<<" , "<<dest.y<<endl;;





	return 0 ;
}
















