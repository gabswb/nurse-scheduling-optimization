bool Chromosome::is_valid()
{
    // Employee timetable array 
    
    // Each mission has to be affected and have the right speciality
    for(Gene gene : this.genes)
    {
        if(!gene.is_affected() && !gene.check_specialty())
            return false;
        
    }
    

    return true;
}