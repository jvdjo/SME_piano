using Microsoft.EntityFrameworkCore;
using SME.Models;

namespace SME.Repository;

public class SmeDbContext : DbContext
{
    public SmeDbContext(DbContextOptions<SmeDbContext> options) : base(options)
    {

    }
    
    public DbSet<Frequencia> Frequencias { get; set; }
}